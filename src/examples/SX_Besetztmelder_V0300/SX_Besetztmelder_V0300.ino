/*******************************************************************************************
 * SX_Belegtmelder_V0300
 *
 * Created:    17.02.2015
 * Copyright:  Reinhard Thamm
 * Version:    V01.00
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
 *
 * 14.11.2015:  --> V03.00:
 *                  Eine neue SX-Library (Änderung SX22b --> SX30) erfordert einige
 *                  Änderungen, die im Code bzw. Kommentaren mit "V03.00" gekennzeichnet sind.
 *                  Diese Version läuft auf der RT-Basisplatine V02.00, jedoch nicht mehr 
 *                  auf den Vorgängerversionen V01.0x), da der SX-Bus beim Schreibvorgang 
 *                  nun über eine Transistor-Endstufe angesteuert wird. Dafür wurden 
 *                  in der in der Lib einige Pin-Definitionen geändert.
 *                  Zum Einlesen des Programmiertasters wird nun der Analogeingang A6 ver-
 *                  wendet.
 *                  Die ISR wird jetzt mit jedem WECHSEL des INT0-Signals (Clock) aufgerufen.
 *                                  
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
#define  PROGBUTTON A6                 // V03.00
#define  DEBOUNCETIME 200

#define  EEPROMSIZE 2                  // 2 Byte vorsehen: Adresse und Abfallverzögerung

char swversion[] =    "SW V03.00";     // V03.00
char hwversion[] =    "HW V02.00";     // V03.00

unsigned occ_count;                    // V03.00 zum Testen

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

#define  MAXPROGPARAM 5
const byte SXAddress     = 0;
const byte SXSettings1   = 1;
const byte SXSettings2   = 2;
const byte SXHWSWVersion = 3;
const byte SXModuleType  = 4;

int      SXtmp[MAXPROGPARAM], oldSXtmp[MAXPROGPARAM], checkedSXtmp[MAXPROGPARAM], 
         orgSXVal[MAXPROGPARAM];

int      progValLimits[MAXPROGPARAM][2] = 
                         {{0, 102},  // SXAddress    lower/upper limit
                          {0, 255},  // SXSettings1
                          {0, 0},    // SXSettings2
                          {0, 0},    // SXHWSWVersion
                          {0, 0}};   // SXModuleType

unsigned long time1;

byte     TrackOn;

volatile boolean running = false;

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
  
//  pinMode(PROGBUTTON, INPUT);                // V03.00
//  digitalWrite(PROGBUTTON, HIGH);            // V03.00

  occ_count = 0;                               // V03.00 zum Testen
  
/*  delay(100);

  if (keypressed()) {
    ClearEEPROM();
    digitalWrite(PROGLED, HIGH);
    delay(200);
    digitalWrite(PROGLED, LOW);
    delay(200);  
  }
*/  
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
void ClearEEPROM () {

  for (int i=0; i<EEPROMSIZE; i++) {
    EEPROM.write(i, 255);
  }
}

//******************************************************************************************
void EEPROMSave() {

  EEPROM.write(0, SXAddr);
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
boolean keypressed() {

  if (analogRead(PROGBUTTON)>512) {      // V03.00
    delay(DEBOUNCETIME);
    if (analogRead(PROGBUTTON)>512) {    // V03.00
      return true;
    }  
  }
  else
    return false;
}

//******************************************************************************************
void saveOldSXValues() {
  
 for (int i=0; i<MAXPROGPARAM; i++) {  
    orgSXVal[i] = sx.get(i+1);
  }
}

//******************************************************************************************
void restoreOldSXValues() {
  
  for (int i=0; i<MAXPROGPARAM; i++) { 
    while (sx.set(i+1, orgSXVal[i])); 
  }
}

//******************************************************************************************
void startProgramming() {
 
  digitalWrite(PROGLED, HIGH);  
  programming = true;
  saveOldSXValues();
  
  for (int i=0; i<MAXPROGPARAM; i++) {  
    switch (i) {
      case SXAddress:     
        while(sx.set(i+1, SXAddr));  
        SXtmp[i]    = SXAddr;
        oldSXtmp[i] = SXAddr;
        checkedSXtmp[i] = SXAddr;
        break;
      case SXSettings1:   
        while(sx.set(i+1, codedDelayTime)); 
        SXtmp[i]    = codedDelayTime;
        oldSXtmp[i] = codedDelayTime;
        checkedSXtmp[i] = codedDelayTime;
        break;
      case SXSettings2:   
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
    running = false;

    TrackOn = sx.getTrackBit();
    if (TrackOn) {                        // Tracksignal = On
      if (programming) {
        finishProgramming();
      }
      else {    // not programming
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
    }    // TrackSignal = On
    
    else {                              // Tracksignal = Off
      if (keypressed()) {
        if (!programming) {
          startProgramming();
        }
        else {    // programming
          finishProgramming();
        }
      }
      else {       // not keypressed
        if (programming) {            // process the received data from SX-bus 
          processProgramming();       
        }
        else {             // not programming
          SXData = sx.get(SXAddr);
          if (SXData != 0) {
            x = sx.set(SXAddr, 0);    // NO occupation signal in case of 
          }                           //    TrackSignal = Off 
        }
      }      
    }    // TrackSignal = Off
  }    // running
 

#ifdef TESTVERSION
  if (millis() > time1+TESTTAKT) {
    time1 = millis();
    
    for (int i=7; i>=0; i--) {
      Serial.print(bitRead(SXOut, i));
      }
    Serial.print(F("  "));
    Serial.print(SXOut);
    
    Serial.print(F("  "));             // V03.00 zum Testen
    Serial.println(occ_count);
    }
#endif
}            //loop

