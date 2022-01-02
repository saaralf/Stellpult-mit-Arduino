#include <Arduino.h>

#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>
//Adafruit_MCP23X17 mcp;
Adafruit_MCP23X17 *mcp[2]; //= new Adafruit_MCP23X17();
#define PINS 32
MCPPin *mcppin[PINS];

void setup()
{
  mcp[0] = new Adafruit_MCP23X17();
  mcp[1] = new Adafruit_MCP23X17();
  Serial.begin(9600);
  if (!mcp[0]->begin_I2C())
  {
    Serial.println("Fehler beim MCP");
  }
  if (!mcp[1]->begin_I2C(0x21))
  {
    Serial.println("Fehler beim MCP 0x21");
  }

  for (int i = 0; i < PINS; i++)
  {
    if (i < 16)
    {
      mcppin[i] = new MCPPin(*mcp[0], 0x20, i);
    }
    if (i > 15)
    {
      mcppin[i] = new MCPPin(*mcp[1], 0x21, i);
    }
  }


  for (int i = 0; i < 16; i++)
  {
    mcp[0]->pinMode(i, OUTPUT);
   mcp[1]->pinMode(i, OUTPUT);
    delay(250);
  }

  Serial.println("Looping...");
}

void loop()
{
  for (int i = 0; i < PINS; i++)
  {
    mcppin[i]->digitalWrite(HIGH);
    Serial.println(i);
    delay(250);
  }
  delay(10);
  //mcppin[0]->writeMCPPin(0,1);
  for (int i = 0; i < PINS; i++)
  {
    mcppin[i]->digitalWrite(LOW);
    delay(250);
  }
  delay(10);
}