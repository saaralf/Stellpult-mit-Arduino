#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#define MAXLEDMCP 5
#define MAXGPIO 16
#define MCP1ADDR 0x20
#define MCP2ADDR 0x21
#define MCP3ADDR 0x22
#define MCP4ADDR 0x23
#define MCP5ADDR 0x24
#define MCP6ADDR 0x25
#define MCP7ADDR 0x26
#define MCP8ADDR 0x27

#define GPIOA [8] = {0, 1, 2, 3, 4, 5, 6, 7}
#define GPIOB [8] = {8, 9, 10, 11, 12, 13, 14, 15}
/*
#                                      /--LED13----------------------
#                                     /   S5RS5G
#                                   LED12
#                                   / 
#                              TW6 /---LED14-------------------------
#                                 /    S4GS4G
#                               LED11
#        TW1           TW2      /
#--LED1---\----LED2----/-LED3--/----LED15----------------------------
#          \          /       TW5  S3RS3G
#           LED4     LED5
#            \      /     TW3
#--LED6-------\LED7/---LED8\--------LED16----------------------------
#        S1GS1R             \
#                           LED9
#                             \            TW7
#--LED10-----------------------\----LED17---\-----LED18--------------
#                       S2GS2R TW4           \
#                                           LED19
#                                              \     S6RS6G
#                                            TW8\----LED20------------
#                                                \   S7RS7G
#                                                 \--LED21------------
*/
//MCP 0 GPIOA 0 -7 -> LED1 - LED7
#define LED1 0 // MCP 0 GPIOA0
#define LED2 1 // MCP 0 GPIOA1
#define LED3 2 // MCP 0 GPIOA2
#define LED4 3 // MCP 0 GPIOA3
#define LED5 4 // MCP 0 GPIOA4
#define LED6 5 // MCP 0 GPIOA5
#define LED7 6 // MCP 0 GPIOA6
#define LED8 7 // MCP 0 GPIOA7

//MCP 0 GPIOB 0 -7 -> LED8 -LED16
#define LED9 8   // MCP 0 GPIOB0
#define LED10 9  // MCP 0 GPIOB1
#define LED11 10 // MCP 0 GPIOB2
#define LED12 11 // MCP 0 GPIOB3
#define LED13 12 // MCP 0 GPIOB4
#define LED14 13 // MCP 0 GPIOB5
#define LED15 14 // MCP 0 GPIOB6
#define LED16 15 // MCP 0 GPIOB7

//MCP 1 GPIOA 0 -4 -> LED17 - LED 21
#define LED17 0 // MCP 1 GPIOA0
#define LED18 1 // MCP 1 GPIOA1
#define LED19 2 // MCP 1 GPIOA2
#define LED20 3 // MCP 1 GPIOA3
#define LED21 4 // MCP 1 GPIOA4

// MCP 1 GPIOA 5 -7 -> Signale 1 - 2
#define SIGNALROT1 5   // Signal 1 Rot   MCP 1 GPIOA5
#define SIGNALGRUEN1 6 // Signal 1 Gruen MCP 1 GPIOA6
#define SIGNALROT2 7   // Signal 2 Rot   MCP 1 GPIOA7
// MCP 1 GPIOB 0 - 7 -> Signale 2 - 7
#define SIGNALGRUEN2 8  // Signal 2 Gruen MCP 1 GPIOB0
#define SIGNALROT3 9    // Signal 3 Rot   MCP 1 GPIOB1
#define SIGNALGRUEN3 10 // Signal 3 Gruen MCP 1 GPIOB2
#define SIGNALROT4 11   // Signal 4 Rot   MCP 1 GPIOB3
#define SIGNALGRUEN4 12 // Signal 4 Gruen MCP 1 GPIOB4
#define SIGNALROT5 13   // Signal 5 Rot   MCP 1 GPIOB5
#define SIGNALGRUEN5 14 // Signal 5 Gruen MCP 1 GPIOB6
#define SIGNALROT6 15   // Signal 6 Rot   MCP 1 GPIOB7
// MCP 2 GPIOA 0 - 2 -> Signal 6 - 7
#define SIGNALGRUEN6 0 // Signal 6 Gruen MCP 2 GPIOA0
#define SIGNALROT7 1   // Signal 7 Rot   MCP 2 GPIOA1
#define SIGNALGRUEN7 2 // Signal 7 Gruen MCP 2 GPIOA2

Adafruit_MCP23X17 mcp[MAXLEDMCP];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  //MCP fÃ¼r LEDs
  mcp[0].begin_I2C(MCP1ADDR); // FÃ¼r LEDs 1 - 16
  mcp[1].begin_I2C(MCP2ADDR); // FÃ¼r LEDs 17 - 21 und Signal 1 - 6
  mcp[2].begin_I2C(MCP3ADDR); // FÃ¼r Signal 6 - 7
  mcp[3].begin_I2C(MCP4ADDR); // FÃ¼r LEDs / Signale
  // MCP fÃ¼r Taster
  mcp[4].begin_I2C(MCP5ADDR); // FÃ¼r Taster
  mcp[5].begin_I2C(MCP6ADDR); // FÃ¼r Taster
  mcp[6].begin_I2C(MCP7ADDR); // FÃ¼r Taster
  mcp[7].begin_I2C(MCP8ADDR); // FÃ¼r Taster

  // Alle GPIO fÃ¼r MCP 1 - 4 als OUTPUT
  for (int gpio = 0; gpio < MAXGPIO; gpio++)
  {
    mcp[0].pinMode(gpio, OUTPUT);
    mcp[1].pinMode(gpio, OUTPUT);
    mcp[2].pinMode(gpio, OUTPUT);
    mcp[3].pinMode(gpio, OUTPUT);
  }
  // Alle LEDs Aus
  mcp[0].writeGPIOAB(LOW);
  mcp[1].writeGPIOAB(LOW);
  mcp[2].writeGPIOAB(LOW);
  mcp[3].writeGPIOAB(LOW);

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

}


void loop()
{
  // put your main code here, to run repeatedly:
}