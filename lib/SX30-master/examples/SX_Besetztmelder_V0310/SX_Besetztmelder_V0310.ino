/*******************************************************************************************
 * SX_Belegtmelder_V0310
 *
 * Created:    17.02.2015
 * Copyright:  Reinhard Thamm
 * Version:    V01.1
 * 
 * Libraries: SX30: Quellen von M.Blank mit Ideen von U.Beyenbach und Änderungen von R.Thamm
 * Zielhardware/-controller: Arduino Pro Mini (5V, 16MHz), ATmega328
 * 
 * Pin2=T0=INT0, Pin4=T1, Pin3=SX-Write-High-Side, Pin6=SX-Write-Low-Side
 *
 * Zum Programmieren des Moduls am SX-Bus werden die SX-Kanäle 1 bis 5 verwendet:
 *
 *   SX-Kanal 1 : SX-Adresse dieses Moduls (0..102)
 *   SX-Kanal 2 : Settings1 (hier: Abfallverzögerungszeit (0..255), mit 25ms/digit, also
 *                                                         20 entspricht 500ms
 *   SX-Kanal 3 : Settings2 (hier nicht benutzt)
 *   SX-Kanal 4 : HW/SW-Version (hier nicht benutzt)
 *   SX-Kanal 5 : Modultyp (hier nicht benutzt)
 *
 * SX-Adresse des Moduls und Abfallverzögerung werden im EEPROM des Controllers abgespeichert.
 * 
 
 * Changes:
 * 28.07.2017:      Key besser entprellt für Start Programmiermodues
 * 12.04.2015:      Zielhardware als #define hinzu. Damit können die Ports eingestellt
 *                  eingestellt werden, auf denen die Hardware das Belegtsignal 
 *                  zurückliefert.
 * 09.05.2015:      Lib SX22 geändert in SX22b.
 *                  Ausgabe der Version im seriellen Monitor.
 * 19.08.2015:      Wenn TrackSignal = Off wird SXOut = 0 gesetzt
 *
 *
 * 24.09.2015:  --> V02.00:
 *                  Programmierung des Moduls geändert auf opensx-Standard (siehe oben
 *                  "Programmieren über die Kanäle 1 bis 5" im Comment);
 *                  Zielhardware als #define entfernt
*******************************************************************************************/
//#define TESTVERSION  // aktiviert serielle Testausgaben und Dialog über Serial Interface

#include <SX30.h>    // Pin2=T0=INT0, Pin4=T1, Pin6=SX-Write  // V03.00
#include <EEPROM.h>


SX30 sx;             //  V03.00

#define  DEFAULTADDR  60               // die Adresse, auf die dieses Modul hört
#define  DEFAULTCODEDDELAYTIME 20      // *25ms = 500ms Abfallverzögerung
#define  DELAYTIMEFACTOR 25            // 1 digit entspricht 25ms

#define  TESTTAKT 1000
#define  LEDTAKT 250
#define  PROGLED 13
        
#define  DEBOUNCETIME 200

#define  PROGBUTTON   A6
#define  PROG_ACTIVATE_TIME  3000      // (muss länger als 3 sec aktiv sein)

#define  EEPROMSIZE 2                  // 2 Byte vorsehen: Adresse und Abfallverzögerung

char swversion[] =    "SW V03.10";     // V03.10
char hwversion[] =    "HW V02.00";     // V02.00

int      SXAddr;
int      err;

byte     SXData;
byte     SXOut;

byte     DataPin[8]     = { 5,  7,  8,  9, 10, 11, 12, A0}; // Pindefinitionen

byte     DataRead[8]    = { 0,  0,  0,  0,  0,  0,  0,  0}; // gelesene Daten
byte     DataOut[8]     = { 0,  0,  0,  0,  0,  0,  0,  0}; // zur Meldung a.d. Zentrale
unsigned long lastOccupied[8] = 
                          { 0,  0,  0,  0,  0,  0,  0,  0}; // Zeitpunkt letzter Belegung
                          
unsigned delayTime;               // Verzögerungszeit gegen Melderflackern
int      codedDelayTime;          // Abbildung in einem Byte: pro Digit=25ms, hier 500ms
                                  //   dieser Wert wird im EEPROM abgelegt
// für den Programmiervorgang über den SX-Bus:
boolean  programming = false;
uint32_t progButtonPressedTime = 0;

#define  MAXPROGPARAM 5
const byte SXAddressIndex     = 0;
const byte SXSettings1Index   = 1;
const byte SXSettings2Index   = 2;
const byte SXHWSWVersion = 3;
const byte SXModuleType  = 4;

int      SXtmp[MAXPROGPARAM], oldSXtmp[MAXPROGPARAM], checkedSXtmp[MAXPROGPARAM], 
         orgSXVal[MAXPROGPARAM];

int      progValLimits[MAXPROGPARAM][2] = 
                         {{1, 102},  // SX Address    lower/upper limit
                          {2, 255},  // SX Settings1
                          {0, 0},    // SX Settings2
                          {0, 0},    // SX HWSWVersion
                          {0, 0}};   // SX ModuleType

unsigned long time1;

byte     TrackOn;

volatile boolean running = false;


static int occ_count = 0; 

//******************************************************************************************
void sxisr(void) {
	// if you want to understand this, see:
	// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1239522239

  sx.isr();
  running = true;
}

//******************************************************************************************
void setup(){
  
#ifdef TESTVERSION
  time1 = millis();
  Serial.begin(115200);
  delay(10);
  Serial.println(swversion);
  Serial.println(hwversion);
#endif


  for (int i=0; i<8; i++) {
    pinMode(DataPin[i], INPUT);
    digitalWrite(DataPin[i], HIGH);
    lastOccupied[i] = millis();
  }
  pinMode(PROGLED, OUTPUT);
  digitalWrite(PROGLED, LOW);

  running = false;
  SXOut = 0;   
 
  if (!EEPROMEmpty()) {
    EEPROMRead();
  } 
  else {
    SXAddr = DEFAULTADDR;
    codedDelayTime = DEFAULTCODEDDELAYTIME;
    delayTime = codedDelayTime * DELAYTIMEFACTOR;
    EEPROMSave();
  }

  sx.init();
//  attachInterrupt(0, sxisr, RISING);            // RISING edge in < V03.00
  attachInterrupt(0, sxisr, CHANGE);              // V03.00
}


//******************************************************************************************
boolean EEPROMEmpty() {
  
  int val;
  boolean empty=true;
  int i=0;
  
  while (empty && (i<EEPROMSIZE)) {
    val = EEPROM.read(i);
    empty = val==255; 
    i++;   
  }
  
#ifdef TESTVERSION
    Serial.print(F("EEPROMEmpty: "));
    if (empty) Serial.println(F("yes")); else Serial.println(F("no"));
#endif

  return empty;
}

//******************************************************************************************
void EEPROMSave() {

  EEPROM.write(0, SXAddr);
  delay(10);
  EEPROM.write(1, codedDelayTime);
}

//******************************************************************************************
void EEPROMRead() {
   
  SXAddr         = EEPROM.read(0);
  codedDelayTime = EEPROM.read(1);
  delayTime      = codedDelayTime * DELAYTIMEFACTOR;
  
#ifdef TESTVERSION
  Serial.println(F("EEPROMRead:"));
  Serial.print(F("SXAddr="));
  Serial.println(SXAddr);
  Serial.print(F("CodedDelayTime="));
  Serial.println(codedDelayTime);
  Serial.print(F("delayTime="));
  Serial.println(delayTime);
  Serial.println();
#endif
}

//******************************************************************************************
void saveOldSXValues() {
  
 for (int i=0; i<MAXPROGPARAM; i++) {  
    orgSXVal[i] = sx.get(i+1);
#ifdef TESTVERSION
  Serial.print(orgSXVal[i]);
  Serial.print(" ");
#endif 
  }
#ifdef TESTVERSION
  Serial.println();
#endif 
}

//******************************************************************************************
void restoreOldSXValues() {
  
  for (int i=0; i<MAXPROGPARAM; i++) { 
    while (sx.set(i+1, orgSXVal[i])); 
    delay(50);
#ifdef TESTVERSION
  Serial.print(orgSXVal[i]);
  Serial.print(" ");
#endif 
  }
#ifdef TESTVERSION
  Serial.println();
#endif 

}

//******************************************************************************************
void startProgramming() {
  
#ifdef TESTVERSION
  Serial.println(F("startProgramming"));
#endif 
  digitalWrite(PROGLED, HIGH);  
  programming = true;
  saveOldSXValues();
  
  for (int i=0; i<MAXPROGPARAM; i++) {  
    switch (i) {
      case SXAddressIndex:     
        while(sx.set(i+1, SXAddr));  
        SXtmp[i]    = SXAddr;
        oldSXtmp[i] = SXAddr;
        checkedSXtmp[i] = SXAddr;
        break;
      case SXSettings1Index:   
        while(sx.set(i+1, codedDelayTime)); 
        SXtmp[i]    = codedDelayTime;
        oldSXtmp[i] = codedDelayTime;
        checkedSXtmp[i] = codedDelayTime;
        break;
      case SXSettings2Index:   
        break;
      case SXHWSWVersion: 
        break;
      case SXModuleType:  
        break;
    }  // switch (i)
  }
}

//******************************************************************************************
void finishProgramming() {

#ifdef TESTVERSION
  Serial.println(F("finishProgramming"));
#endif
  SXAddr         = checkedSXtmp[0];
  codedDelayTime = checkedSXtmp[1];
      
  EEPROMSave();
  EEPROMRead();
  restoreOldSXValues();
  delay(80);
  programming = false;
  digitalWrite(PROGLED, LOW); 
}

//******************************************************************************************
void processProgramming() {

  for (int i=0; i<MAXPROGPARAM; i++) { 
    SXtmp[i] = sx.get(i+1); 
    if (SXtmp[i] != oldSXtmp[i]) {        // value has been changed
      if ((SXtmp[i] >= progValLimits[i][0]) && (SXtmp[i] <= progValLimits[i][1])) {  // within predefined limits?
        checkedSXtmp[i] = SXtmp[i];       // accept value
        oldSXtmp[i]        = SXtmp[i];
      }
      else {  // out of limits
        SXtmp[i] = oldSXtmp[i];           // reset value
        while (sx.set(i+1, SXtmp[i]));     // also on the SX-Bus
      }
    }
  }
}

//******************************************************************************************
void loop() {

  int x;
  
  if (running) {
    running = false;   // set to true in isr  

    TrackOn = sx.getTrackBit();
    if (TrackOn) {                        // Tracksignal = On
      if (programming) {
         finishProgramming();
      } else {    // not programming
        for (int i=0; i<8; i++) {
          DataRead[i] = digitalRead(DataPin[i]);    // active low Input: Data[i]==0 = Belegt!
          if (!DataRead[i]) { // --> belegt!

            if (DataRead[i] != DataOut[i]) {        // V03.00 zum Testen
              occ_count++;
            }
            
            DataOut[i] = DataRead[i];
            lastOccupied[i] = millis();                   
          }
          else  {            // frei!
            if (millis() > lastOccupied[i] + delayTime) { // delayTime abgelaufen?
              DataOut[i] = DataRead[i]; 
            }
          }
          bitWrite(SXOut, i, !DataOut[i]);
        }
      
        SXData = sx.get(SXAddr);
        if (SXData != SXOut) {
          x = sx.set(SXAddr, SXOut);
        }  
      }  // not programming
    } else {  // Tracksignal = Off
        int a = analogRead(PROGBUTTON);
        if (a < 1000) {    // key = active high (~1023)
          progButtonPressedTime = millis();
        } 
        if ((millis() - progButtonPressedTime) > PROG_ACTIVATE_TIME ) {
           if (!programming) {
              startProgramming();
              progButtonPressedTime = millis();
           } else {
              finishProgramming();
              progButtonPressedTime = millis();
           }
        }
        if (programming) {            // process the received data from SX-bus 
          processProgramming();       
        }
        else {  // not programming
          SXData = sx.get(SXAddr);
          if (SXData != 0) {
            x = sx.set(SXAddr, 0);    // NO occupation signal in case of 
          }                           //    TrackSignal = Off 
        } // programming  
    }   // TrackSignal = Off
  } else {
    // no sx signal, reset button
    progButtonPressedTime = millis();
  }
 

#ifdef TESTVERSION
  if (millis() > time1+TESTTAKT) {
    time1 = millis();
    
    for (int i=7; i>=0; i--) {
      Serial.print(bitRead(SXOut, i));
      }
    Serial.print("  ");
    Serial.print(SXOut);
    
    Serial.print("  ");             // V03.00 zum Testen
    Serial.print(occ_count);
    int a = analogRead(A6);
    Serial.print("  "); 
    Serial.println(a);
    }
#endif
}            //loop
