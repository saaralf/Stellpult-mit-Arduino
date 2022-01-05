#include <Arduino.h>
#include <MCP23017.h>

//#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>

#define INT_PIN 2
#define PINS 48
#define MCPS 4
MCP23017 mcp[MCPS];
void handleInterrupt();

MCPPin *mcppin[PINS];

int interruptPin2 = 2;
int interruptPin3 = 3;

volatile bool event1;

volatile bool event2;
byte intCapRegA;
byte intCapRegB;

void eventHappened1()
{
  if (!event1)
  {
    event1 = true;
  }
}
void eventHappened2()
{
  event2 = true;
}

void setup()
{
  pinMode(interruptPin2, INPUT);

  pinMode(interruptPin3, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), eventHappened1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), eventHappened2, CHANGE);

  Serial.begin(9600);
  delay(200);
  Wire.begin();
  for (int i = 0; i < MCPS; i++)
  {
    Serial.print("MCP: ");
    Serial.println(0x20 + i, HEX);
    mcp[i] = MCP23017(0x20 + i);
    mcp[i].Init();
    if (i == 2 || i == 3)
    {
      Serial.println("SetzeInterupts für ");
      Serial.println(i, HEX);
    }
  }

  mcp[2].setInterruptPinPol(HIGH); // set INTA and INTB active-high

  mcp[2].setInterruptOnChangePort(B11111111, A); //set all B pins as interrrupt Pins
  mcp[2].setInterruptOnChangePort(B11111111, B); //set all B pins as interrrupt Pins
  //mcp[2].setIntMirror(1);
  // mcp[3].setInterruptPinPol(HIGH); // set INTA and INTB active-high

  //mcp[3].setInterruptOnChangePort(B11111111, A); //set all B pins as interrrupt Pins
  event1 = false;
  event2 = false;

  for (int i = 0; i < PINS; i++)
  {
    if (i < 16)
    {
      mcppin[i] = new MCPPin(mcp[0], 0x20, i < 8 ? B : A, i); // wenn i <8 Dann soll er GPB sein
      mcppin[i]->setPinDirection(OUTPUT); // Diese sind INPUT PINS
    }
    if (i > 15 && i < 32)
    {
      mcppin[i] = new MCPPin(mcp[1], 0x21, i < 24? B : A, i);// wenn i <24 Dann soll er GPB sein
      mcppin[i]->setPinDirection(OUTPUT); // Diese sind INPUT PINS
    }                                     /*
    if (i > 31 && i < 48)
    {
      mcppin[i] = new MCPPin(mcp[2], 0x22, i);
      mcppin[i]->setPinDirection(INPUT); // Diese sind INPUT PINS
      mcppin[i]->setupInterruptPin();
    } /*
   if (i > 47)
    {
      mcppin[i] = new MCPPin(*mcp[3], 0x23, i);
      mcppin[i]->setPinDirection(INPUT); // Diese sind INPUT PINS
      mcppin[i]->setupInterruptPin();
    }*/
  }

  /*
  for (int i = 0; i < 16; i++)
  {
    mcp[0]->pinMode(i, OUTPUT);
   mcp[1]->pinMode(i, OUTPUT);
    delay(250);
  }
*/

  // OPTIONAL - call this to override defaults
  // mirror INTA/B so only one wire required
  // active drive so INTA/B will not be floating
  // INTA/B will be signaled with a LOW

  // configure button pin for input with pull up

  Serial.println("Looping...");
}

void checkInterruptMPCX()
{
}

void loop()
{

  intCapRegA = mcp[2].getIntCap(A); // ensures that existing interrupts are cleared
  intCapRegB = mcp[2].getIntCap(B); // ensures that existing interrupts are cleared
  if (event1)
  {
    event1 = false;

    Serial.println("Interrupt! A");

    delay(200);
    byte intFlagRegA, eventPin;
    intFlagRegA = mcp[2].getIntFlag(A);
    eventPin = log(intFlagRegA) / log(2);
    intCapRegA = mcp[2].getIntCap(A);
    Serial.print(log(intFlagRegA > 0 ? intFlagRegA : intCapRegA > 0 ? intCapRegA
                                                                    : -1) /
                 log(2));
    eventPin = log(intFlagRegA > 0 ? intFlagRegA : intCapRegA > 0 ? intCapRegA
                                                                  : 100000000) /
               log(2);
               int pinnummer = 0x20*1000+A*10+eventPin;
    Serial.print("Interrupt Flag Register: ");
    Serial.println(intFlagRegA, BIN);
    Serial.print("Interrupt Capture Register: ");
    Serial.println(intCapRegA, BIN);
    Serial.print("Pin No.");
  //  Serial.print(eventPin < 8 ? eventPin : -1);
    Serial.print(pinnummer);
    Serial.print(" went ");
    if ((intFlagRegA & intCapRegA) == 0)
    { //LOW-HIGH or HIGH-LOW interrupt?
      Serial.println("LOW");
    }
    else
    {
      Serial.println("HIGH");
    }
    // mcp[2].setPort(intFlagRegA, A);
    delay(1000);
    event1 = false;
  }
  if (event2)
  {
    event2 = false;

    Serial.println("Interrupt! B");

    delay(200);
    byte intFlagRegB, eventPin;
    intFlagRegB = mcp[2].getIntFlag(B);
    eventPin = log(intFlagRegB) / log(2);
    intCapRegB = mcp[2].getIntCap(B);
    Serial.print("Interrupt Flag Register: ");
    Serial.println(intFlagRegB, BIN);
    Serial.print("Interrupt Capture Register: ");
    Serial.println(intCapRegB, BIN);
    Serial.print("Pin No.");
    Serial.print(eventPin);
    Serial.print(" went ");
    if ((intFlagRegB & intCapRegB) == 0)
    { //LOW-HIGH or HIGH-LOW interrupt?
      Serial.println("LOW");
    }
    else
    {
      Serial.println("HIGH");
    }
    //  mcp[2].setPort(intFlagRegB, B);
    delay(1000);
    event2 = false;
  }
  /*
  if (event1)
  {
   delay(200);
    byte intFlagReg, eventPin;
    intFlagReg = mcp[3].getIntFlag(B);
    eventPin = log(intFlagReg) / log(2);
    intCapReg2 = mcp[3].getIntCap(B);
    Serial.println("Interrupt!");
    Serial.print("Interrupt Flag Register: ");
    Serial.println(intFlagReg, BIN);
    Serial.print("Interrupt Capture Register: ");
    Serial.println(intCapReg2, BIN);
    Serial.print("Pin No.");
    Serial.print(eventPin);
    Serial.print(" went ");
    if ((intFlagReg & intCapReg2) == 0)
    { //LOW-HIGH or HIGH-LOW interrupt?
      Serial.println("LOW");
    }
    else
    {
      Serial.println("HIGH");
    }
    mcp[3].setPort(intFlagReg, B);
    //delay(1000);
    event2 = false;
  }
  
*/

  for (int i = 0; i < 32; i++)
  {
    mcppin[i]->digitalWrite(HIGH);

    //Serial.println(mcppin[i]->getPinName());
  }
  delay(10);
  //mcppin[0]->writeMCPPin(0,1);
  for (int i = 0; i < 32; i++)
  {
    mcppin[i]->digitalWrite(LOW);
  }
  delay(10);
}
