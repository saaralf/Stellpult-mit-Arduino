#include <Arduino.h>
#include <MCP23017.h>

//#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>

#define INT_PIN 2
#define PINS 48
#define MCPS 3
MCP23017 mcp[MCPS];
void handleInterrupt();

MCPPin *mcppin[PINS];

int interruptPin = 2;
volatile bool event; 
byte intCapReg; 
void eventHappened(){
  event = true;
}
void setup()
{
   pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), eventHappened, CHANGE);
  Serial.begin(9600);
  delay(200);
  Wire.begin();
  for (int i = 0; i < MCPS; i++)
  {
    Serial.print("MCP: ");
    Serial.println(0x20 + i, HEX);
    mcp[i] =  MCP23017(0x20 + i);
    mcp[i].Init();
    if (i == 2 || i == 3)
    {
      Serial.println("SetzeInterupts für ");
      Serial.println(i, HEX);

    }
  }
  
  mcp[2].setInterruptPinPol(HIGH); // set INTA and INTB active-high
  
  mcp[2].setInterruptOnChangePort(B11111111, A); //set all B pins as interrrupt Pins
  event=false;
  for (int i = 0; i < PINS; i++)
  {
    if (i < 16)
    {
      mcppin[i] = new MCPPin(mcp[0], 0x20, i);
      mcppin[i]->setPinDirection(OUTPUT); // Diese sind INPUT PINS
    }
    if (i > 15 && i < 32)
    {
      mcppin[i] = new MCPPin(mcp[1], 0x21, i);
      mcppin[i]->setPinDirection(OUTPUT); // Diese sind INPUT PINS
    }/*
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

void loop()
{
  
   intCapReg = mcp[2].getIntCap(A); // ensures that existing interrupts are cleared
  if(event){
    delay(200);
    byte intFlagReg, eventPin; 
    intFlagReg = mcp[2].getIntFlag(A);
    eventPin = log(intFlagReg)/log(2);
    intCapReg = mcp[2].getIntCap(A);
    Serial.println("Interrupt!");
    Serial.print("Interrupt Flag Register: ");
    Serial.println(intFlagReg,BIN); 
    Serial.print("Interrupt Capture Register: ");
    Serial.println(intCapReg,BIN); 
    Serial.print("Pin No.");
    Serial.print(eventPin);
    Serial.print(" went ");
    if((intFlagReg&intCapReg) == 0){  //LOW-HIGH or HIGH-LOW interrupt?
      Serial.println("LOW");
    }
    else{
      Serial.println("HIGH");
    }
    mcp[2].setPort(intFlagReg,A);
    //delay(1000);
    event = false; 
  }
 

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
