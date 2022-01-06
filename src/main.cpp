#include <Arduino.h>
#include <MCP23017.h>

//#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>

#define INT_PIN 2
#define PINS 64
#define MCPS 4
MCP23017 mcp[MCPS];
void handleInterrupt();

unsigned berechnePinNummer(int mcpAdresse, MCP_PORT port, int pinnummer);

int reversePinNummer(int mpcadresse, MCP_PORT port, unsigned int pinnnummer);

MCPPin *mcppin[PINS];

// Variablen für die Interrupts definieren
/*
// Es gibt 5 Interrupt Pins am Mega2560 und diese werden an 3 MCPs angeschlossen
// PIN 2 und 3 an MCP 1 (0x22) INT A und INT B
// PIN 18 und 19 an MCP 2 (0x23) INT A und INT B
// PIN X  an MCP X (0x27) INT A oder INT B, jenachdem welcher Port Input wird
*/
int interruptPin2 = 2;
int interruptPin3 = 3;
int interruptPin18 = 18;
int interruptPin19 = 19;

volatile bool intPin2EventA;
volatile bool intPin2EventB;

volatile bool intPin3EventA;
volatile bool intPin3EventB;

volatile bool intPin18EventA;
volatile bool intPin18EventB;

volatile bool intPin19EventA;
volatile bool intPin19EventB;

byte intPin2CapRegA;
byte intPin2CapRegB;

byte intPin3CapRegA;
byte intPin3CapRegB;

byte intPin18CapRegA;
byte intPin18CapRegB;

byte intPin19CapRegA;
byte intPin19CapRegB;

void ISRPIN2()
{

  intPin2EventA = true;
}
void ISRPIN3()
{
  intPin3EventB = true;
}
void ISRPIN18()
{

  intPin18EventA = true;
}
void ISRPIN19()
{
  intPin19EventB = true;
}

void setup()
{
  pinMode(interruptPin2, INPUT);
  pinMode(interruptPin3, INPUT);
  pinMode(interruptPin18, INPUT);
  pinMode(interruptPin19, INPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPin2), ISRPIN2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), ISRPIN3, CHANGE);

  attachInterrupt(digitalPinToInterrupt(interruptPin18), ISRPIN18, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin19), ISRPIN19, CHANGE);

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

  mcp[3].setInterruptPinPol(HIGH); // set INTA and INTB active-high

  mcp[2].setInterruptOnChangePort(B11111111, A); //set all B pins as interrrupt Pins
  mcp[2].setInterruptOnChangePort(B11111111, B); //set all B pins as interrrupt Pins

  mcp[3].setInterruptOnChangePort(B11111111, A); //set all B pins as interrrupt Pins
  mcp[3].setInterruptOnChangePort(B11111111, B); //set all B pins as interrrupt Pins
  //mcp[2].setIntMirror(1);
  // mcp[3].setInterruptPinPol(HIGH); // set INTA and INTB active-high

  //mcp[3].setInterruptOnChangePort(B11111111, A); //set all B pins as interrrupt Pins
  intPin2EventA = false;
  intPin3EventB = false;
  intPin18EventA = false;
  intPin18EventB = false;
  for (int i = 0; i < PINS; i++)
  {
    if (i < 16)
    {
      mcppin[i] = new MCPPin(mcp[0], 0x20, i < 8 ? B : A, i); // wenn i <8 Dann soll er GPB sein
      mcppin[i]->setPinDirection(OUTPUT);                     // Diese sind INPUT PINS
    }
    if (i > 15 && i < 32)
    {
      mcppin[i] = new MCPPin(mcp[1], 0x21, i < 24 ? B : A, i); // wenn i <24 Dann soll er GPB sein
      mcppin[i]->setPinDirection(OUTPUT);                      // Diese sind INPUT PINS
    }
    if (i > 31 && i < 48)
    {
      mcppin[i] = new MCPPin(mcp[2], 0x22, i < 40 ? B : A, i);
      mcppin[i]->setPinDirection(INPUT); // Diese sind INPUT PINS
    }
    if (i > 47)
    {
      mcppin[i] = new MCPPin(mcp[3], 0x23, i < 56 ? B : A, i);
      mcppin[i]->setPinDirection(INPUT); // Diese sind INPUT PINS
    }
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
Serial.print (intPin18EventA);
  intPin2CapRegA = mcp[2].getIntCap(A); // ensures that existing interrupts are cleared
  intPin2CapRegB = mcp[2].getIntCap(B); // ensures that existing interrupts are cleared
  handleInterrupt();
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

void handleInterrupt()
{

  if (intPin2EventA)
  {
    intPin2EventA = false;

    Serial.println("Interrupt! A");

    delay(200);
    byte intFlagRegA, eventPin;
    intFlagRegA = mcp[2].getIntFlag(A);
    eventPin = log(intFlagRegA) / log(2);
    intPin2CapRegA = mcp[2].getIntCap(A);
    Serial.print(log(intFlagRegA > 0 ? intFlagRegA : intPin2CapRegA > 0 ? intPin2CapRegA
                                                                        : -1) /
                 log(2));
    eventPin = log(intFlagRegA > 0 ? intFlagRegA : intPin2CapRegA > 0 ? intPin2CapRegA
                                                                      : 100000000) /
               log(2);
    unsigned int pinnummer = berechnePinNummer(0x22, A, eventPin);
    Serial.print("Interrupt Flag Register: ");
    Serial.println(intFlagRegA, BIN);
    Serial.print("Interrupt Capture Register: ");
    Serial.println(intPin2CapRegA, BIN);
    Serial.print("Pin No.");
    //  Serial.print(eventPin < 8 ? eventPin : -1);
    Serial.print(pinnummer);
    Serial.print(" went ");
    if ((intFlagRegA & intPin2CapRegA) == 0)
    { //LOW-HIGH or HIGH-LOW interrupt?
      Serial.println("LOW");
    }
    else
    {
      Serial.println("HIGH");
    }
    // mcp[2].setPort(intFlagRegA, A);
    delay(1000);
    intPin2EventA = false;
  }

  if (intPin3EventB)
  {
    intPin3EventB = false;

    Serial.println("Interrupt! B");

    delay(200);
    byte intFlagRegB, eventPin;
    intFlagRegB = mcp[2].getIntFlag(B);
    eventPin = log(intFlagRegB) / log(2);
    intPin3CapRegB = mcp[2].getIntCap(B);
    unsigned pinnummer = berechnePinNummer(0x22, B, eventPin);

    Serial.print("Interrupt Flag Register: ");
    Serial.println(intFlagRegB, BIN);
    Serial.print("Interrupt Capture Register: ");
    Serial.println(intPin3CapRegB, BIN);
    Serial.print("Pin No.");
    Serial.print(pinnummer);
    Serial.print(" went ");
    if ((intFlagRegB & intPin3CapRegB) == 0)
    { //LOW-HIGH or HIGH-LOW interrupt?
      Serial.println("LOW");
    }
    else
    {
      Serial.println("HIGH");
    }
    //  mcp[2].setPort(intFlagRegB, B);
    delay(1000);
    intPin3EventB = false;
  }

  if (intPin18EventA)
  {
    intPin18EventA = false;

    Serial.println("Interrupt! B");

    delay(200);
    byte intFlagRegB, eventPin;
    intFlagRegB = mcp[3].getIntFlag(B);
    eventPin = log(intFlagRegB) / log(2);
    intPin18CapRegB = mcp[3].getIntCap(B);
    unsigned pinnummer = berechnePinNummer(0x23, B, eventPin);

    Serial.print("Interrupt Flag Register: ");
    Serial.println(intFlagRegB, BIN);
    Serial.print("Interrupt Capture Register: ");
    Serial.println(intPin18CapRegB, BIN);
    Serial.print("Pin No.");
    Serial.print(pinnummer);
    Serial.print(" went ");
    if ((intFlagRegB & intPin18CapRegB) == 0)
    { //LOW-HIGH or HIGH-LOW interrupt?
      Serial.println("LOW");
    }
    else
    {
      Serial.println("HIGH");
    }
    //  mcp[2].setPort(intFlagRegB, B);
    delay(1000);
    intPin18EventA = false;
  }
}

unsigned int berechnePinNummer(int mcpAdresse, MCP_PORT port, int pinnummer)
{
  return (mcpAdresse * 1000) + ((port + 1) * 100) + pinnummer;
}
int reversePinNummer(int mpcadresse, MCP_PORT port, unsigned int pinnnummer)
{

  return pinnnummer - ((mpcadresse * 1000) + ((port + 1) * 100));
}