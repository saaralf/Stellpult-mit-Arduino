

#include <Arduino.h>
//#include <Stellpult.h>
//#include <MCP.h>
#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>
#include <Weiche.h>
#include <WeichenTaster.h>
#include <interrupt.h>
#include <MCPPin.h>
/*
//                                      /--LED19----------------------LED22---\
//                                     /   S5RS5G                              \
//                                    /                                         \
//                                   /                                           \
//                              TW6 /---LED18--------------------------LED23------\
//                                 /    S4GS4G                                     \
//                               LED20                                              LED24
//        TW1           TW2      /                                                   \
//--LED1---\----LED2----/-LED3--/----LED17-----------------------------LED25---------------LED26----/-----LED27----------
//          \          /       TW5  S3RS3G                                                         /
//           LED4     LED5                                                                        LED28
//            \      /     TW3                                                                   /
//--LED6-------\LED7/---LED8\--------LED16--------------------------------LED29 ---------/------/--------------LED30------
//        S1GS1R             \                                                          /
//                           LED10                                                     LED31
//                             \            TW7                                       /
//--LED9------------------------\----LED11---\-----LED15--------------LED32----------/
//                       S2GS2R TW4           \                                     /         /--LED41-----
//                                           LED12                                LED33      /
//                                              \     S6RS6G                      /         /----LED40-----
//                                            TW8\----LED14------------LED34-----/         /
//                                                \   S7RS7G                    LED35     LED38
//                                                 \--LED13------------LED36---/-LED37---/----LED39---------
//
*/

// Anzahl der GPIO der MCP23017
#define MAXGPIO 16

bool DEBUG = true;

#define MAXMCP 8

// Variablen die das Stellpult beschreiben
#define NUMBERWEICHEN 17 // Anzahl der Weichen im Stellpult
#define NUMBERSIGNALE 16 // Anzahl der Signale im Stellpult
#define MAXPIN 128
/*
//Interupts Pins auf dem Arduino Mega 2560 sind
//2, 3, 18, 19, 20, 21
// (pins 20 & 21 are not available to use for interrupts while they are used for I2C communication)
*/
// Definiere die Interupt Pins für die Eingabe MCP23017

#define INT_PIN_TAST_MCP0 2      // Pin 2 muss mit dem MCP INTA mit dem TAST_MCP0 verbunden werden
#define INT_PIN_TAST_MCP1 3      // Pin 3 muss mit dem MCP INTA mit dem TAST_MCP1 verbunden werden
#define INT_PIN_TAST_MCP2 18     // Pin 18 muss mit dem MCP INTA mit dem TAST_MCP2 verbunden werden
#define INT_PIN_LED_TAST_MCP0 19 // Pin 19 muss mit dem MCP INTA mit dem LED_TAST_MCP0 verbunden werden
bool awakenByInterrupt1;
// Methoden bekannt geben
void mcpauswerten();
void handleInterrupt();
void intCallBack();

Adafruit_MCP23X17 *mcp = new Adafruit_MCP23X17();
MCPPin *mcppin[MAXPIN];

// für jede Weiche im Stellpult ein Objekt anlegen
Weiche *weiche[NUMBERWEICHEN];
WeichenTaster *weichenTaster[NUMBERWEICHEN];
byte ledPin = 13;
static uint16_t ledState = 0;

// Stellpult *stellpult = new Stellpult();
void setup()
{

  for (int i = 0; i < NUMBERWEICHEN; i++)
  {
    *weiche[i] = Weiche();
  }
  for (int i = 0; i < MAXPIN; i++)
  {
    *mcppin[i] = MCPPin(*mcp, 0x20, 0);
  }
  for (int i = 0; i < NUMBERWEICHEN; i++)
  {
    *weichenTaster[i] = WeichenTaster(*mcppin[0]);
    weichenTaster[i]->addWeiche(*weiche[i]);
  }

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  // Interupt Pins des Arduino setzen
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  // pinMode(INT_PIN_TAST_MCP2, INPUT_PULLUP);
  // pinMode(INT_PIN_LED_TAST_MCP0, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), intCallBack1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), intCallBack, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(INT_PIN_TAST_MCP2), intCallBack, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(INT_PIN_LED_TAST_MCP0), intCallBack, CHANGE);
  Serial.println("Erzeuge 17 Weichen"); // 17 Weichen im Hauptbahnhof
  // Erzeuge Zustände für Weichen
  // Alle Weichen sollen im Zustand gerade beginnen. false bedeutet gerade

  digitalWrite(ledPin, LOW);

  Serial.println("Looping...");
}

void loop()
{
  /*if (!digitalRead(2))
  {

    Serial.print (TAST_MCP0.getLastInterruptPin());
    //    handleInterrupt();
    }
        if (!digitalRead(3))
  { Serial.print (TAST_MCP1.getLastInterruptPin());


  }*/
  if (awakenByInterrupt1)
  {
    Serial.println(weichenTaster1->isPressed());

    handleInterrupt();
  }
  /*
 if (mcp.digitalRead(0)) {
    Serial.println("Button Pressed!");
    delay(250);
  }
  */

  Serial.print(".");
  delay(250); // debounce
}

/*
for (int i=0; i<NUMBERWEICHEN;i++)
{
  Serial.print("Weiche ");
  Serial.print(weiche[i].getName());
  Serial.print(" ");
  Serial.print(weiche[i].getRichtungText());

  Serial.println("");

}
    delay(1000);
*/
// Serial.println("Auswerten");

/*
  delay(550);
  WEICHE1 = false;
  WEICHE2 = false;
  WEICHE3 = false;
  WEICHE4 = false;
  WEICHE5 = true;
  WEICHE6 = false;
  WEICHE7 = false;
}

  mcpauswerten();

  delay(550);
  WEICHE5 = false;
  WEICHE6 = true;
  WEICHE7 = true;



*/

//  mcpauswerten();

/*
  for (int gpio = 0; gpio < MAXGPIO; gpio++)
  {

    if (mcp4.digitalRead(gpio))
    {
      if (gpio < 8)
      {
        Serial.print("GPIOA");
        Serial.print(gpio);
        Serial.println(" gedrückt");
      }
      else
      {
        Serial.print("GPIOB");
        Serial.print(gpio - 8);
        Serial.println(" gedrückt");
      }
    }
    /*
    Serial.println(gpio);

    mcp0.digitalWrite(gpio, HIGH);
    mcp1.digitalWrite(gpio, HIGH);
    mcp2.digitalWrite(gpio, HIGH);
    mcp3.digitalWrite(gpio, HIGH);

  }
  delay(550);

  for (int gpio = 0; gpio < MAXGPIO; gpio++)
  {
    Serial.println(gpio);

    mcp0.digitalWrite(gpio, LOW);
    mcp1.digitalWrite(gpio, LOW);
    mcp2.digitalWrite(gpio, LOW);
    mcp3.digitalWrite(gpio, LOW);
*/
//}

void mcpauswerten()
{

  // Weiche 1 und Weiche 2
  if (!weiche[0].getRichtung() && !weiche[1].getRichtung()) // Weiche 1 Gerade und Weiche 2 gerade
  {
    //        TW1           TW2      /                                                   \ 
    //--LED1---\----LED2----/-LED3--/----LED15-----------------------------LED25---------------LED26----/-----LED27----------
    //          \          /       TW5  S3RS3G                                                         /
    //           LED4     LED5                                                                        LED28
    //            \      /     TW3                                                                   /
    //--LED6-------\LED7/---LED8

    Serial.println("Weiche 1und 2 gerade");
    mcp[0]->digitalWrite(LED1, HIGH); // Ausfahrgleis
    mcp[0]->digitalWrite(LED2, HIGH);
    mcp[0]->digitalWrite(LED3, HIGH);
    mcp[0]->digitalWrite(LED4, LOW);
    mcp[0]->digitalWrite(LED5, LOW);
    mcp[0]->digitalWrite(LED7, HIGH);
    mcp[0]->digitalWrite(LED8, HIGH);
    mcp[0]->digitalWrite(LED6, HIGH); // Einfahrgleis
    // Signal Einfahrgleis ROT
    mcp[1]->digitalWrite(SIGNALROT1, HIGH);
    mcp[1]->digitalWrite(SIGNALROT2, LOW);
  }
  if (weiche[0].getRichtung() && weiche[1].getRichtung())
  {
    mcp[0]->digitalWrite(LED1, HIGH);
    mcp[0]->digitalWrite(LED2, LOW);
    mcp[0]->digitalWrite(LED3, HIGH);
    mcp[0]->digitalWrite(LED4, HIGH);
    mcp[0]->digitalWrite(LED5, HIGH);
    mcp[0]->digitalWrite(LED6, LOW);
    mcp[0]->digitalWrite(LED7, HIGH);
    mcp[0]->digitalWrite(LED8, LOW);
    // Signal Einfahrgleis ROT
    mcp[1]->digitalWrite(SIGNALROT1, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN1, LOW);
  }
  // Ende Weiche 1 und Weiche 2

  // Weiche 3
  if (!weiche[2].getRichtung()) // Weiche 3 ist gerade
  {
    if (weiche[1].getRichtung()) // Weiche 2 abzweig, dann stecke nach weiche 2 aus
    {
      mcp[0]->digitalWrite(LED8, LOW);
    }
    else
    {
      mcp[0]->digitalWrite(LED8, HIGH);
    }

    mcp[0]->digitalWrite(LED10, LOW);
    mcp[0]->digitalWrite(LED16, HIGH);
  }
  if (weiche[2].getRichtung())
  {
    Serial.println("Weiche3 abzweig");
    if (weiche[1].getRichtung())
    {
      mcp[0]->digitalWrite(LED8, LOW);
    }
    else
    {
      mcp[0]->digitalWrite(LED8, HIGH);
    }
    if (!weiche[3].getRichtung()) // weiche 4 gerade
    {
      mcp[0]->digitalWrite(LED10, LOW);
    }
    if (weiche[3].getRichtung()) // weiche 4 abzweig
    {
      mcp[0]->digitalWrite(LED10, HIGH);

      mcp[0]->digitalWrite(LED16, LOW);
    }
  }
  // Ende Weiche 3
  // Weiche 4
  if (!weiche[3].getRichtung()) // Weiche 4 ist gerade
  {
    if (weiche[2].getRichtung()) // Weiche 3 ist abzweig dann weg nach 3 an
    {
      mcp[0]->digitalWrite(LED10, HIGH);
    }
    else
    {
      mcp[0]->digitalWrite(LED10, LOW);
    }

    mcp[0]->digitalWrite(LED9, HIGH);
    mcp[0]->digitalWrite(LED11, HIGH);

    mcp[1]->digitalWrite(SIGNALROT2, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN2, LOW);
  }

  // Weiche 4
  if (weiche[3].getRichtung()) // Weiche 4 ist abzweig
  {
    if (weiche[2].getRichtung()) // Weiche 3 ist abzweig dann weg nach weiche 3 an
    {
      mcp[0]->digitalWrite(LED10, HIGH);
    }
    else
    {
      mcp[0]->digitalWrite(LED10, LOW); // weiche 4 ist gerade
    }
    mcp[0]->digitalWrite(LED9, LOW);
    mcp[0]->digitalWrite(LED11, HIGH);

    // Signal Abstellgleis ROT
    mcp[1]->digitalWrite(SIGNALROT2, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN2, LOW);
  }
  // ENDE Weiche 4
  //  Weiche 5
  if (weiche[4].getRichtung()) // TRUE Weiche 5 ist abzweig

  {
    //                              TW6 /---LED18--------------------------LED23------\
//                                 /    S4GS4G                                     \
//                               LED20                                              LED24
    //        TW1           TW2      /                                                   \ 
//--LED1---\----LED2----/-LED3--/----LED17-----------------------------LED25---------------LED26----/-----LED27----------
    Serial.println("Weiche5 ist abzweig");

    mcp[1]->digitalWrite(LED20, HIGH);

    mcp[1]->digitalWrite(LED17, LOW);

    mcp[1]->digitalWrite(SIGNALROT5, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN5, LOW);
  }

  if (!weiche[4].getRichtung()) // Weiche 5 ist gerade

  {
    //                              TW6 /---LED18--------------------------LED23------\
//                                 /    S4GS4G                                     \
//                               LED20                                              LED24
    //        TW1           TW2      /                                                   \ 
//--LED1---\----LED2----/-LED3--/----LED17-----------------------------LED25---------------LED26----/-----LED27----------
    Serial.println("Weiche5 ist gerade");
    mcp[1]->digitalWrite(LED20, LOW);

    mcp[1]->digitalWrite(LED17, HIGH);
  }
  // Ende Weiche 5

  // Weiche 6
  //                                    /--LED19----------------------LED22---\
//                                     /   S5RS5G                              \
//                                    /                                         \
//                                   /                                           \
//                              TW6 /---LED18--------------------------LED23------\
//                                 /    S4GS4G                                     \
//                               LED20                                              LED24
  if (weiche[5].getRichtung()) // Weiche 6 ist abzweig
  {
    mcp[1]->digitalWrite(LED18, HIGH);
    mcp[1]->digitalWrite(LED19, LOW);
    if (weiche[4].getRichtung())
    {
      mcp[1]->digitalWrite(LED20, HIGH);
    }
    if (!weiche[4].getRichtung())
    {
      mcp[1]->digitalWrite(LED20, LOW);
    }

    mcp[1]->digitalWrite(SIGNALROT3, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN3, LOW);
  }
  if (!weiche[5].getRichtung()) // Weiche 6 ist gerade
  {
    mcp[1]->digitalWrite(LED18, LOW);
    mcp[1]->digitalWrite(LED19, HIGH);
    if (weiche[4].getRichtung())
    {
      mcp[1]->digitalWrite(LED20, HIGH);
    }
    if (!weiche[4].getRichtung())
    {
      mcp[1]->digitalWrite(LED20, LOW);
    }

    mcp[1]->digitalWrite(SIGNALROT4, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN4, LOW);
  }
  // ENDE WEICHE 6

  // Weiche 7
  //                           LED10                                                     LED31
  //                             \            TW7                                       /
  //--LED9------------------------\----LED11---\-----LED15--------------LED32----------/
  //                       S2GS2R TW4           \                                     /         /--LED41-----
  //                                           LED12                                LED33      /
  //                                              \     S6RS6G                      /         /----LED40-----
  //                                            TW8\----LED14------------LED34-----/         /
  if (weiche[6].getRichtung()) // Weiche 7 auf abzweig
  {
    mcp[0]->digitalWrite(LED15, LOW);
    mcp[0]->digitalWrite(LED12, HIGH);
    mcp[0]->digitalWrite(LED11, HIGH);

    mcp[1]->digitalWrite(SIGNALROT6, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN6, LOW);
  }
  if (!weiche[6].getRichtung()) // Weiche 7 auf gerade
  {
    mcp[0]->digitalWrite(LED15, HIGH);
    mcp[0]->digitalWrite(LED12, LOW);
    mcp[0]->digitalWrite(LED11, HIGH);

    mcp[1]->digitalWrite(SIGNALROT6, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN6, LOW);
  }

  // ENDE WEICHE 8

  // Weiche 8
  //                           LED10                                                     LED31
  //                             \            TW7                                       /
  //--LED9------------------------\----LED11---\-----LED15--------------LED32----------/
  //                       S2GS2R TW4           \                                     /         /--LED41-----
  //                                           LED12                                LED33      /
  //                                              \     S6RS6G                      /         /----LED40-----
  //                                            TW8\----LED14------------LED34-----/         /
  //                                                \   S7RS7G                    LED35     LED38
  //                                                 \--LED13------------LED36---/-LED37---/----LED39---------
  //
  if (weiche[7].getRichtung()) // Weiche 8 auf abzweig
  {
    mcp[0]->digitalWrite(LED14, HIGH);

    mcp[0]->digitalWrite(LED13, LOW);
  }
  if (!weiche[7].getRichtung()) // Weiche 8 auf gerade
  {
    mcp[0]->digitalWrite(LED14, LOW);

    mcp[0]->digitalWrite(LED13, HIGH);
  }

  // ENDE WEICHE 8
}
* /