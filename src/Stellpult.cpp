#include <Stellpult.h>
    Adafruit_MCP23X17 mcp[MAXLEDMCP];

bool Stellpult::begin (){

    Adafruit_MCP23X17 mcp[MAXLEDMCP];

if (!mcp[0].begin_I2C())
  {
    //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1)
      return false;
  }
  if (!mcp[1].begin_I2C(MCP2ADDR))
  {
    //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1)
       return false;
  }

//MCP fÃ¼r LEDs
  // uncomment appropriate mcp.begin

  /*
  mcp[1].begin_I2C(MCP2ADDR); // FÃ¼r LEDs 17 - 21 und Signal 1 - 6
  mcp[2].begin_I2C(MCP3ADDR); // FÃ¼r Signal 6 - 7
  mcp[3].begin_I2C(MCP4ADDR); // FÃ¼r LEDs / Signale
  // MCP fÃ¼r Taster
  mcp[4].begin_I2C(MCP5ADDR); // FÃ¼r Taster
  mcp[5].begin_I2C(MCP6ADDR); // FÃ¼r Taster
  mcp[6].begin_I2C(MCP7ADDR); // FÃ¼r Taster
  mcp[7].begin_I2C(MCP8ADDR); // FÃ¼r Taster
*/

  // Alle GPIO fÃ¼r MCP 1 - 4 als OUTPUT
  for (int gpio = 0; gpio < MAXGPIO; gpio++)
  {
    mcp[0].pinMode(gpio, OUTPUT);
    mcp[1].pinMode(gpio, OUTPUT);
    //   mcp[2].pinMode(gpio, OUTPUT);
    //   mcp[3].pinMode(gpio, OUTPUT);
  }
  /*
  for (int gpio = 0; gpio < MAXGPIO; gpio++)
  {
    mcp[4].pinMode(gpio, INPUT_PULLUP);
    mcp[5].pinMode(gpio, INPUT_PULLUP);
    mcp[6].pinMode(gpio, INPUT_PULLUP);
    mcp[7].pinMode(gpio, INPUT_PULLUP);
  }
  */
  // Alle LEDs Aus

  mcp[0].writeGPIOAB(LOW);
  mcp[1].writeGPIOAB(LOW);
  //mcp[2].writeGPIOAB(LOW);
  //mcp[3].writeGPIOAB(LOW);
  /*
  //Signale auf Rot und GrÃ¼n aus
  mcp[1].digitalWrite(SIGNALROT1, HIGH);
  mcp[1].digitalWrite(SIGNALROT3, HIGH);
  mcp[1].digitalWrite(SIGNALROT4, HIGH);
  mcp[1].digitalWrite(SIGNALROT5, HIGH);
  mcp[1].digitalWrite(SIGNALROT6, HIGH);
  mcp[1].digitalWrite(SIGNALROT7, HIGH);
  mcp[1].digitalWrite(SIGNALGRUEN1, LOW);
  mcp[1].digitalWrite(SIGNALGRUEN2, LOW);
  mcp[1].digitalWrite(SIGNALGRUEN3, LOW);
  mcp[1].digitalWrite(SIGNALGRUEN4, LOW);
  mcp[1].digitalWrite(SIGNALGRUEN5, LOW);
  mcp[2].digitalWrite(SIGNALGRUEN6, LOW);
  mcp[2].digitalWrite(SIGNALGRUEN7, LOW);

  */

 WEICHE1 = false;  // False gerade, true abzweig
 WEICHE2 = false;  // False gerade, true abzweig
 WEICHE3 = false;  // False gerade, true abzweig
 WEICHE4 = false;  // False gerade, true abzweig
 WEICHE5 = false;  // False gerade, true abzweig
 WEICHE6 = false;  // False gerade, true abzweig
 WEICHE7 = false;  // False gerade, true abzweig
 WEICHE8 = false;  // False gerade, true abzweig
 WEICHE9 = false;  // False gerade, true abzweig
 WEICHE10 = false; // False gerade, true abzweig
 WEICHE11 = false; // False gerade, true abzweig
 WEICHE12 = false; // False gerade, true abzweig
 WEICHE13 = false; // False gerade, true abzweig
 WEICHE14 = false; // False gerade, true abzweig
 return true;
};





void Stellpult::mcpauswerten()
{
  // Weiche 1 und Weiche 2
  if (!WEICHE1 && !WEICHE2) // Weiche 1 Gerade und Weiche 2 gerade
  {
    /*//        TW1           TW2      /                                                   \ 
    //--LED1---\----LED2----/-LED3--/----LED15-----------------------------LED25---------------LED26----/-----LED27----------
    //          \          /       TW5  S3RS3G                                                         /
    //           LED4     LED5                                                                        LED28
    //            \      /     TW3                                                                   /
    //--LED6-------\LED7/---LED8
*/
Serial.println("Weiche 1und 2 gerade");
    mcp[0].digitalWrite(LED1, HIGH); //Ausfahrgleis
    mcp[0].digitalWrite(LED2, HIGH);
    mcp[0].digitalWrite(LED3, HIGH);
    mcp[0].digitalWrite(LED4, LOW);
    mcp[0].digitalWrite(LED5, LOW);
    mcp[0].digitalWrite(LED7, HIGH);
    mcp[0].digitalWrite(LED8, HIGH);
    mcp[0].digitalWrite(LED6, HIGH); // Einfahrgleis
    //Signal Einfahrgleis ROT
    mcp[1].digitalWrite(SIGNALROT1, HIGH);
    mcp[1].digitalWrite(SIGNALROT2, LOW);
  }
  if (WEICHE1 && WEICHE2)
  {
    mcp[0].digitalWrite(LED1, HIGH);
    mcp[0].digitalWrite(LED2, LOW);
    mcp[0].digitalWrite(LED3, HIGH);
    mcp[0].digitalWrite(LED4, HIGH);
    mcp[0].digitalWrite(LED5, HIGH);
    mcp[0].digitalWrite(LED6, LOW);
    mcp[0].digitalWrite(LED7, HIGH);
    mcp[0].digitalWrite(LED8, LOW);
    //Signal Einfahrgleis ROT
    mcp[1].digitalWrite(SIGNALROT1, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN1, LOW);
  }
  // Ende Weiche 1 und Weiche 2

  // Weiche 3
  if (!WEICHE3) // Weiche 3 ist gerade
  {
    if (WEICHE2) // Weiche 2 abzweig, dann stecke nach weiche 2 aus
    {
      mcp[0].digitalWrite(LED8, LOW);
    }
    else
    {
      mcp[0].digitalWrite(LED8, HIGH);
    }

    mcp[0].digitalWrite(LED10, LOW);
    mcp[0].digitalWrite(LED16, HIGH);
  }
  if (WEICHE3)
  {
    Serial.println("Weiche3 abzweig");
    if (WEICHE2)
    {
      mcp[0].digitalWrite(LED8, LOW);
    }
    else
    {
      mcp[0].digitalWrite(LED8, HIGH);
    }
    if (!WEICHE4) // weiche 4 gerade
    {
      mcp[0].digitalWrite(LED10, LOW);
    }
    if (WEICHE4) // weiche 4 abzweig
    {
      mcp[0].digitalWrite(LED10, HIGH);

      mcp[0].digitalWrite(LED16, LOW);
    }
  }
  // Ende Weiche 3
  //Weiche 4
  if (!WEICHE4) // Weiche 4 ist gerade
  {
    if (WEICHE3) //Weiche 3 ist abzweig dann weg nach 3 an
    {
      mcp[0].digitalWrite(LED10, HIGH);
    }
    else
    {
      mcp[0].digitalWrite(LED10, LOW);
    }

    mcp[0].digitalWrite(LED9, HIGH);
    mcp[0].digitalWrite(LED11, HIGH);

    mcp[1].digitalWrite(SIGNALROT2, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN2, LOW);
  }

  //Weiche 4
  if (WEICHE4) // Weiche 4 ist abzweig
  {
    if (WEICHE3) // Weiche 3 ist abzweig dann weg nach weiche 3 an
    {
      mcp[0].digitalWrite(LED10, HIGH);
    }
    else
    {
      mcp[0].digitalWrite(LED10, LOW); // weiche 4 ist gerade
    }
    mcp[0].digitalWrite(LED9, LOW);
    mcp[0].digitalWrite(LED11, HIGH);

    //Signal Abstellgleis ROT
    mcp[1].digitalWrite(SIGNALROT2, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN2, LOW);
  }
  //ENDE Weiche 4
  // Weiche 5
  if (WEICHE5) // TRUE Weiche 5 ist abzweig

  {
    /*//                              TW6 /---LED18--------------------------LED23------\
//                                 /    S4GS4G                                     \
//                               LED20                                              LED24
    //        TW1           TW2      /                                                   \ 
//--LED1---\----LED2----/-LED3--/----LED17-----------------------------LED25---------------LED26----/-----LED27----------*/
    Serial.println("Weiche5 ist abzweig");

    mcp[1].digitalWrite(LED20, HIGH);

    mcp[1].digitalWrite(LED17, LOW);

    mcp[1].digitalWrite(SIGNALROT5, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN5, LOW);
  }

  if (!WEICHE5) // Weiche 5 ist gerade

  {
    /*//                              TW6 /---LED18--------------------------LED23------\
//                                 /    S4GS4G                                     \
//                               LED20                                              LED24
    //        TW1           TW2      /                                                   \ 
//--LED1---\----LED2----/-LED3--/----LED17-----------------------------LED25---------------LED26----/-----LED27----------*/
    Serial.println("Weiche5 ist gerade");
    mcp[1].digitalWrite(LED20, LOW);

    mcp[1].digitalWrite(LED17, HIGH);
  }
  // Ende Weiche 5

  // Weiche 6
  /*//                                      /--LED19----------------------LED22---\
//                                     /   S5RS5G                              \
//                                    /                                         \
//                                   /                                           \
//                              TW6 /---LED18--------------------------LED23------\
//                                 /    S4GS4G                                     \
//                               LED20                                              LED24*/
  if (WEICHE6) // Weiche 6 ist abzweig
  {
    mcp[1].digitalWrite(LED18, HIGH);
    mcp[1].digitalWrite(LED19, LOW);
    if (WEICHE5)
    {
      mcp[1].digitalWrite(LED20, HIGH);
    }
    if (!WEICHE5)
    {
      mcp[1].digitalWrite(LED20, LOW);
    }

    mcp[1].digitalWrite(SIGNALROT3, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN3, LOW);
  }
  if (!WEICHE6) // Weiche 6 ist gerade
  {
    mcp[1].digitalWrite(LED18, LOW);
    mcp[1].digitalWrite(LED19, HIGH);
    if (WEICHE5)
    {
      mcp[1].digitalWrite(LED20, HIGH);
    }
    if (!WEICHE5)
    {
      mcp[1].digitalWrite(LED20, LOW);
    }

    mcp[1].digitalWrite(SIGNALROT4, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN4, LOW);
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
  if (WEICHE7) // Weiche 7 auf abzweig
  {
    mcp[0].digitalWrite(LED15, LOW);
    mcp[0].digitalWrite(LED12, HIGH);
    mcp[0].digitalWrite(LED11, HIGH);

    mcp[1].digitalWrite(SIGNALROT6, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN6, LOW);
  }
  if (!WEICHE7) // Weiche 7 auf gerade
  {
    mcp[0].digitalWrite(LED15, HIGH);
    mcp[0].digitalWrite(LED12, LOW);
    mcp[0].digitalWrite(LED11, HIGH);

    mcp[1].digitalWrite(SIGNALROT6, HIGH);
    mcp[1].digitalWrite(SIGNALGRUEN6, LOW);
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
  if (WEICHE8) // Weiche 8 auf abzweig
  {
    mcp[0].digitalWrite(LED14, HIGH);

    mcp[0].digitalWrite(LED13, LOW);
  }
  if (!WEICHE8) // Weiche 8 auf gerade
  {
    mcp[0].digitalWrite(LED14, LOW);

    mcp[0].digitalWrite(LED13, HIGH);
  }

  // ENDE WEICHE 8
}

