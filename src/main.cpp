

#include <Arduino.h>
//#include <Stellpult.h>
#include <MCP.h>
#include <Weiche.h>
#define GPIOA [8] = {0, 1, 2, 3, 4, 5, 6, 7}
#define GPIOB [8] = {8, 9, 10, 11, 12, 13, 14, 15}

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
//Definiere die Ports für MCP0x20 PORTA und PORTB für Adafruit MCP23017
#define MCP0X20GPA0 0
#define MCP0X20GPA1 1
#define MCP0X20GPA2 2
#define MCP0X20GPA3 3
#define MCP0X20GPA4 4
#define MCP0X20GPA5 5
#define MCP0X20GPA6 6
#define MCP0X20GPA7 7

#define MCP0X20GPB0 8
#define MCP0X20GPB1 9
#define MCP0X20GPB2 10
#define MCP0X20GPB3 11
#define MCP0X20GPB4 12
#define MCP0X20GPB5 13
#define MCP0X20GPB6 14
#define MCP0X20GPB7 15

//Definiere die Ports für MCP0x21 PORTA und PORTB für Adafruit MCP23017
#define MCP0X21GPA0 0
#define MCP0X21GPA1 1
#define MCP0X21GPA2 2
#define MCP0X21GPA3 3
#define MCP0X21GPA4 4 //Signal 1
#define MCP0X21GPA5 5 //Signal 1
#define MCP0X21GPA6 6 //Signal 2
#define MCP0X21GPA7 7 //Signal 2

#define MCP0X21GPB0 8  //Signal 3
#define MCP0X21GPB1 9  //Signal 3
#define MCP0X21GPB2 10 //Signal 4
#define MCP0X21GPB3 11 //Signal 4
#define MCP0X21GPB4 12 //Signal 5
#define MCP0X21GPB5 13 //Signal 5
#define MCP0X21GPB6 14 //Signal 6
#define MCP0X21GPB7 15 //Signal 6

//MCP 0 GPIOA 0 -7 -> LED1 - LED7
#define LED1 MCP0X20GPA0 // MCP 0 GPIOA0
#define LED2 MCP0X20GPA1 // MCP 0 GPIOA1
#define LED3 MCP0X20GPA2 // MCP 0 GPIOA2
#define LED4 MCP0X20GPA3 // MCP 0 GPIOA3
#define LED5 MCP0X20GPA4 // MCP 0 GPIOA4
#define LED6 MCP0X20GPA5 // MCP 0 GPIOA5
#define LED7 MCP0X20GPA6 // MCP 0 GPIOA6
#define LED8 MCP0X20GPA7 // MCP 0 GPIOA7

//MCP 0 GPIOB 0 -7 -> LED8 -LED16
#define LED9 MCP0X20GPB0  // MCP 0 GPIOB0
#define LED10 MCP0X20GPB1 // MCP 0 GPIOB1
#define LED11 MCP0X20GPB2 // MCP 0 GPIOB2
#define LED12 MCP0X20GPB3 // MCP 0 GPIOB3
#define LED13 MCP0X20GPB4 // MCP 0 GPIOB4
#define LED14 MCP0X20GPB5 // MCP 0 GPIOB5
#define LED15 MCP0X20GPB6 // MCP 0 GPIOB6
#define LED16 MCP0X20GPB7 // MCP 0 GPIOB7

//MCP 1 GPIOA 0 -4 -> LED17 - LED 21
#define LED17 MCP0X21GPA0 // MCP 1 GPIOA0
#define LED18 MCP0X21GPA1 // MCP 1 GPIOA1
#define LED19 MCP0X21GPA2 // MCP 1 GPIOA2
#define LED20 MCP0X21GPA3 // MCP 1 GPIOA3
// MCP 1 GPIOA 5 -7 -> Signale 1 - 2
#define SIGNALROT1 MCP0X21GPA4   // Signal 1 Rot   MCP 1 GPIOA4
#define SIGNALGRUEN1 MCP0X21GPA5 // Signal 1 Gruen MCP 1 GPIOA5
#define SIGNALROT2 MCP0X21GPA6   // Signal 2 Rot   MCP 1 GPIOA6
#define SIGNALGRUEN2 MCP0X21GPA7 // Signal 2 Gruen MCP 1 GPIOA7

// MCP 1 GPIOB 0 - 7 -> Signale 2 - 7
#define SIGNALROT3 MCP0X21GPB0   // Signal 3 Rot   MCP 1 GPIOB0
#define SIGNALGRUEN3 MCP0X21GPB1 // Signal 3 Gruen MCP 1 GPIOB1
#define SIGNALROT4 MCP0X21GPB2   // Signal 4 Rot   MCP 1 GPIOB2
#define SIGNALGRUEN4 MCP0X21GPB3 // Signal 4 Gruen MCP 1 GPIOB3
#define SIGNALROT5 MCP0X21GPB4   // Signal 5 Rot   MCP 1 GPIOB4
#define SIGNALGRUEN5 MCP0X21GPB5 // Signal 5 Gruen MCP 1 GPIOB5
#define SIGNALROT6 MCP0X21GPB6   // Signal 6 Rot   MCP 1 GPIOB6
#define SIGNALGRUEN6 MCP0X21GPB7 // Signal 6 Gruen MCP 1 GPIOB7
// MCP 2 GPIOA 0 - 2 -> Signal 6 - 7
#define SIGNALROT7 1   // Signal 7 Rot   MCP 2 GPIOA1
#define SIGNALGRUEN7 2 // Signal 7 Gruen MCP 2 GPIOA2

//MCP 2 GPIOA 3-7 -> LED 22 - 25
#define LED22 3 // MCP 2 GPIOA3
#define LED23 4 // MCP 2 GPIOA4
#define LED24 5 // MCP 2 GPIOA5
#define LED25 6 // MCP 2 GPIOA6
#define LED26 7 // MCP 2 GPIOA7
//MCP 2 GPIOB 0 - 7 -> LED 25 - LED XX
#define LED27 8  // MCP 2 GPIOB0
#define LED28 9  // MCP 2 GPIOB1
#define LED29 10 // MCP 2 GPIOB2
#define LED30 11 // MCP 2 GPIOB3
#define LED31 12 // MCP 2 GPIOB4
#define LED32 13 // MCP 2 GPIOB5
#define LED33 14 // MCP 2 GPIOB6
#define LED34 15 // MCP 2 GPIOB7

#define SIGNALROT8 0     // Signal 8 Rot   MCP 3 GPIOA0
#define SIGNALGRUEN8 1   // Signal 8 Gruen MCP 3 GPIOA1
#define SIGNALROT9 2     // Signal 9 Rot   MCP 3 GPIOA2
#define SIGNALGRUEN9 3   // Signal 9 Gruen MCP 3 GPIOA3
#define SIGNALROT10 4    // Signal 10 Rot   MCP 3 GPIOA4
#define SIGNALGRUEN10 5  // Signal 10 Gruen MCP 3 GPIOA5
#define SIGNALROT11 6    // Signal 11 Rot   MCP 3 GPIOA6
#define SIGNALGRUEN11 7  // Signal 11 Gruen MCP 3 GPIOA7
#define SIGNALROT12 8    // Signal 12 Rot   MCP 3 GPIOB0
#define SIGNALGRUEN12 9  // Signal 12 Gruen MCP 3 GPIOB1
#define SIGNALROT13 10   // Signal 13 Rot   MCP 3 GPIOB2
#define SIGNALGRUEN13 11 // Signal 13 Gruen MCP 3 GPIOB3
#define SIGNALROT14 12   // Signal 14 Rot   MCP 3 GPIOB4
#define SIGNALGRUEN14 13 // Signal 14 Gruen MCP 3 GPIOB5
#define SIGNALROT15 14   // Signal 15 Rot   MCP 3 GPIOB6
#define SIGNALGRUEN15 15 // Signal 15 Gruen MCP 3 GPIOB7
#define SIGNALROT16 0    // Signal 16 Rot   MCP 4 GPIOA0
#define SIGNALGRUEN16 0  // Signal 16 Gruen MCP 4 GPIOA1
#define MAXGPIO 16

#define NUMBERWEICHEN 17
#define MAXLEDMCP 2
#define MAXTASTERMCP 3

void mcpauswerten();
MCP *mcp[MAXLEDMCP];
//Adafruit_MCP23X17 mcpLED[MAXLEDMCP];
//Adafruit_MCP23X17 mcpTaster[MAXTASTERMCP];

Weiche weiche[NUMBERWEICHEN];

//Stellpult *stellpult = new Stellpult();
void setup()
{
  Serial.begin(9600);

  Serial.println("Erzeuge 17 Weichen"); //17 Weichen im Hauptbahnhof

  for (int i; i <= NUMBERWEICHEN; i++)
  {
    weiche[i] =  Weiche("Weiche" + i, false);
  }

  Serial.print("Erzeuge MCPs: ");
  //Serial.println(0x20 + mcps, HEX);
  mcp[0] = new MCP("MCP 1", 0x20); // LEDs und Signale
  mcp[1] = new MCP("MCP 2", 0x21); // LEDs und Signale
  mcp[2] = new MCP("MCP 3", 0x22); // LEDs und Signale
  mcp[3] = new MCP("MCP 4", 0x23); // LEDs und Signale
  mcp[4] = new MCP("MCP 5", 0x24); // LEDs und Signale
  mcp[5] = new MCP("MCP 6", 0x25); // Taster Weichen und Signale
  mcp[6] = new MCP("MCP 7", 0x26); // Taster Weichen und Signale
                                   //mcp[7] = new MCP ("MCP 1",0x27);

  for (int i = 0; i < MAXGPIO; i++)
  {
    mcp[0]->pinMode(i, OUTPUT);
    mcp[1]->pinMode(i, OUTPUT);
    mcp[2]->pinMode(i, OUTPUT);
    mcp[3]->pinMode(i, OUTPUT);
    mcp[4]->pinMode(i, OUTPUT);
    mcp[5]->pinMode(i, INPUT_PULLUP);
    mcp[6]->pinMode(i, INPUT_PULLUP);
  }

  //mcp = new MCP ( MAXLEDMCP);

  //for (int gpio = 0; gpio < MAXGPIO; gpio++)
  //{
  // Serial.print("Setze PinMode für PIN ");
  //Serial.println(gpio);
  //mcp->pinMode(gpio  , INPUT_PULLUP);

  //   mcp[2].pinMode(gpio, OUTPUT);
  //   mcp[3].pinMode(gpio, OUTPUT);

  //}

  // configure pin for output
  // mcp.pinMode(LED_PIN, OUTPUT);

  Serial.println("Looping...");
}

void loop()
{
  //Serial.println("Auswerten");

  for (int i = 0; i < 16; i++)
  {
    if (mcp[5]->digitalRead(i))
    {
      if (i < 8)
      {
        Serial.print("GPIOA");
        Serial.print(i);
        Serial.println(" gedrückt");
      }
      else
      {
        Serial.print("GPIOB");
        Serial.print(i - 8);
        Serial.println(" gedrückt");
      }
    }
  }
  /*
  delay(550);
  WEICHE1 = false;
  WEICHE2 = false;
  WEICHE3 = false;
  WEICHE4 = false;
  WEICHE5 = true;
  WEICHE6 = false;
  WEICHE7 = false;

  mcpauswerten();

  delay(550);
  WEICHE5 = false;
  WEICHE6 = true;
  WEICHE7 = true;



  mcpauswerten();
  */
  /*
  for (int mcps=0; mcps<MAXLEDMCP;mcps++){
  for (int gpio = 0; gpio < MAXGPIO; gpio++)
  {
    Serial.println(gpio);

    mcp->digitalWrite(gpio, HIGH);
    delay(1000);
  }
  delay(550);

  for (int gpio = 0; gpio < MAXGPIO; gpio++)
  {
    Serial.println(gpio);

    mcp->digitalWrite(gpio, LOW);
    delay(1000);
  }
  }
*/
}

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
    mcp[0]->digitalWrite(LED1, HIGH); //Ausfahrgleis
    mcp[0]->digitalWrite(LED2, HIGH);
    mcp[0]->digitalWrite(LED3, HIGH);
    mcp[0]->digitalWrite(LED4, LOW);
    mcp[0]->digitalWrite(LED5, LOW);
    mcp[0]->digitalWrite(LED7, HIGH);
    mcp[0]->digitalWrite(LED8, HIGH);
    mcp[0]->digitalWrite(LED6, HIGH); // Einfahrgleis
    //Signal Einfahrgleis ROT
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
    //Signal Einfahrgleis ROT
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
  //Weiche 4
  if (!weiche[3].getRichtung()) // Weiche 4 ist gerade
  {
    if (weiche[2].getRichtung()) //Weiche 3 ist abzweig dann weg nach 3 an
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

  //Weiche 4
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

    //Signal Abstellgleis ROT
    mcp[1]->digitalWrite(SIGNALROT2, HIGH);
    mcp[1]->digitalWrite(SIGNALGRUEN2, LOW);
  }
  //ENDE Weiche 4
  // Weiche 5
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
