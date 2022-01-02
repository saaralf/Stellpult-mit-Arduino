

#include <Arduino.h>
//#include <Stellpult.h>
//#include <MCP.h>
#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>
Adafruit_MCP23X17 *mcp1[1]; //= new Adafruit_MCP23X17();

MCPPin *mcppin[16];
//MCPPin *mcppin;


// Stellpult *stellpult = new Stellpult();
void setup()
{
  Serial.begin(9600);
delay(250);
  //if (!mcp.begin_I2C(0x21))
  //{
   Serial.println("Erzeuge MCPs");
  // }
  mcp1[0] = new Adafruit_MCP23X17();
 /* mcp1[1] = new Adafruit_MCP23X17();
  mcp1[2] = new Adafruit_MCP23X17();
  mcp1[3] = new Adafruit_MCP23X17();

  if (!mcp1[0]->begin_I2C(0x20))
  {
    Serial.println("Fehler bei 0x20");
  }

  if (!mcp1[1]->begin_I2C(0x21))
  {
    Serial.println("Fehler 0x21");
  }
/*
  if (!mcp1[2]->begin_I2C(0x24))
  {
    Serial.println("Fehler 0x24");
  }

  if (!mcp1[3]->begin_I2C(0x25))
  {
    Serial.println("Fehler 0x25");
  }*/
   Serial.println("Fertig MCPs");

   Serial.println("Erzeuge MCPPins");

  for (int i = 0; i < 16; i++)
  {
    
    
      mcppin[i] = new MCPPin(*mcp1[0], 0x20, i);
    }
  for (int i = 16; i < 32; i++)
  {

      mcppin[i] = new MCPPin(*mcp1[1], 0x21, i);
    }
    /*
    if (i>31 && i < 48)
    {
      mcppin[i] = new MCPPin(*mcp1[2], 0x24, i);
    }
    if (i>47 &&i < 64)
    {
      mcppin[i] = new MCPPin(*mcp1[3], 0x25, i);
    }
  */
  


  Serial.println("Looping...");
}

void loop()
{
/*
  if (mcppin[33]->readMCPPin())
  {
    Serial.println(mcppin[33]->readMCPPin());
    delay(250);
  }
  */
  // mcppin[0]->writeMCPPin(0,0);#
  
  for (int i = 0; i < 16; i++)
  {
    //mcp.digitalWrite(i, HIGH);
    mcppin[i]->digitalWrite(HIGH);
delay(250);
  }
  delay(1000);
  //mcppin[0]->writeMCPPin(0,1);
  for (int i = 0; i < 16; i++)
  {
    //mcp.digitalWrite(i, LOW);
    //mcp1->digitalWrite(i,LOW);

    mcppin[i]->digitalWrite(LOW);
delay(250);

  }
  delay(1000);
  
}