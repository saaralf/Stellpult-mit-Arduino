

#include <Arduino.h>
//#include <Stellpult.h>
//#include <MCP.h>
#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>
bool DEBUG = false;
Adafruit_MCP23X17 *mcp1[4]; //= new Adafruit_MCP23X17();
//Adafruit_MCP23X17 mcp;

MCPPin *mcppin[32];
//MCPPin *mcppin;

byte ledPin = 13;
static uint16_t ledState = 0;

// Stellpult *stellpult = new Stellpult();
void setup()
{
  Serial.begin(9600);

  //if (!mcp.begin_I2C(0x21))
  //{
  //  Serial.println("Fehler");
  // }
  mcp1[0] = new Adafruit_MCP23X17();
  mcp1[1] = new Adafruit_MCP23X17();
  mcp1[2] = new Adafruit_MCP23X17();
  mcp1[3] = new Adafruit_MCP23X17();
  if (!mcp1[0]->begin_I2C(0x20))
  {
    Serial.println("Fehler bei 0x20");
  }

  if (!mcp1[1]->begin_I2C(0x21))
  {
    Serial.println("Fehler");
  }


  if (!mcp1[2]->begin_I2C(0x24))
  {
    Serial.println("Fehler 0x24");
  }
 
  if (!mcp1[3]->begin_I2C(0x25))
   {
    Serial.println("Fehler 0x25");
   }

  for (int i = 0; i < 16; i++)
  {
    mcppin[i] = new MCPPin(*mcp1[0], 0x20, i);
  }
  for (int i = 16; i < 32; i++)
  {
    mcppin[i] = new MCPPin(*mcp1[1], 0x21, i);
  }
   for (int i = 32; i < 48; i++)
  {
    mcppin[i] = new MCPPin(*mcp1[2], 0x24, i);
  }
   for (int i = 48; i < 64; i++)
  {
    mcppin[i] = new MCPPin(*mcp1[3], 0x25, i);
  }
  /*
mcp1[2]->pinMode(0,INPUT);
mcp1[2]->pinMode(1,INPUT);
mcp1[2]->pinMode(2,INPUT);
mcp1[2]->pinMode(3,INPUT);
mcp1[2]->pinMode(4,INPUT);
mcp1[2]->pinMode(5,INPUT);
mcp1[2]->pinMode(6,INPUT);
mcp1[2]->pinMode(7,INPUT);
mcp1[2]->pinMode(8,INPUT);
mcp1[2]->pinMode(9,INPUT);
mcp1[2]->pinMode(10,INPUT);
mcp1[2]->pinMode(11,INPUT);
mcp1[2]->pinMode(12,INPUT);
mcp1[2]->pinMode(13,INPUT);
mcp1[2]->pinMode(14,INPUT);
mcp1[2]->pinMode(15,INPUT);
mcp1[2]->pinMode(16,INPUT);

  for (int i = 32; i < 48; i++)
  {
    mcppin[i] = new MCPPin(*mcp1[2], 0x24, i, INPUT);
  }*/
  /*
  mcppin[0] = new MCPPin(*mcp1[0], 0x21, 0);
  mcppin[1] = new MCPPin(*mcp1[0], 0x21, 1);
  mcppin[2] = new MCPPin(*mcp1[0], 0x21, 2);
  mcppin[3] = new MCPPin(*mcp1[0], 0x21, 3);
  mcppin[4] = new MCPPin(*mcp1[0], 0x21, 4);
  mcppin[5] = new MCPPin(*mcp1[0], 0x21, 5);
  mcppin[6] = new MCPPin(*mcp1[0], 0x21, 6);
  mcppin[7] = new MCPPin(*mcp1[0], 0x21, 7);
  mcppin[8] = new MCPPin(*mcp1[0], 0x21, 8);
  mcppin[9] = new MCPPin(*mcp1[0], 0x21, 9);
  mcppin[10] = new MCPPin(*mcp1[0], 0x21, 10);
  mcppin[11] = new MCPPin(*mcp1[0], 0x21, 11);
  mcppin[12] = new MCPPin(*mcp1[0], 0x21, 12);
  mcppin[13] = new MCPPin(*mcp1[0], 0x21, 13);
  mcppin[14] = new MCPPin(*mcp1[0], 0x21, 14);
  mcppin[15] = new MCPPin(*mcp1[0], 0x21, 15);

  mcppin[16] = new MCPPin(*mcp1[1], 0x20, 16);
  mcppin[17] = new MCPPin(*mcp1[1], 0x20, 17);
  mcppin[18] = new MCPPin(*mcp1[1], 0x20, 18);
  mcppin[19] = new MCPPin(*mcp1[1], 0x20, 19);
  mcppin[20] = new MCPPin(*mcp1[1], 0x20, 20);
  mcppin[21] = new MCPPin(*mcp1[1], 0x20, 21);
  mcppin[22] = new MCPPin(*mcp1[1], 0x20, 22);
  mcppin[23] = new MCPPin(*mcp1[1], 0x20, 23);
  mcppin[24] = new MCPPin(*mcp1[1], 0x20, 24);
  mcppin[25] = new MCPPin(*mcp1[1], 0x20, 25);
  mcppin[26] = new MCPPin(*mcp1[1], 0x20, 26);
  mcppin[27] = new MCPPin(*mcp1[1], 0x20, 27);
  mcppin[28] = new MCPPin(*mcp1[1], 0x20, 28);
  mcppin[29] = new MCPPin(*mcp1[1], 0x20, 29);
  mcppin[30] = new MCPPin(*mcp1[1], 0x20, 30);
  mcppin[31] = new MCPPin(*mcp1[1], 0x20, 31);

  /*

/*
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);

  mcp.digitalWrite(0, HIGH);
  mcp.digitalWrite(1, HIGH);
  mcp.digitalWrite(2, HIGH);
  mcp.digitalWrite(3, HIGH);
  mcp.digitalWrite(4, HIGH);
  mcp.digitalWrite(5, HIGH);
  mcp.digitalWrite(6, HIGH);
  mcp.digitalWrite(7, HIGH);
*/
  /*
mcp1->pinMode(0,OUTPUT);
mcp1->pinMode(1,OUTPUT);
mcp1->pinMode(2,OUTPUT);
mcp1->pinMode(3,OUTPUT);
mcp1->pinMode(4,OUTPUT);
mcp1->pinMode(5,OUTPUT);
mcp1->pinMode(6,OUTPUT);
mcp1->pinMode(7,OUTPUT);

mcp1->digitalWrite(0,HIGH);
mcp1->digitalWrite(1,HIGH);
mcp1->digitalWrite(2,HIGH);
mcp1->digitalWrite(3,HIGH);
mcp1->digitalWrite(4,HIGH);
mcp1->digitalWrite(5,HIGH);
mcp1->digitalWrite(6,HIGH);
mcp1->digitalWrite(7,HIGH);
*/
  pinMode(ledPin, OUTPUT);

  Serial.println("Looping...");
}

void loop()
{

 Serial.println(sizeof(mcppin));

 Serial.println(mcppin[8]->getPinName());
  Serial.println (mcppin[8]->getAdresse(),HEX);
  Serial.println (mcppin[8]->getPinNummer());
  Serial.println (mcppin[8]->getPinDirection());
  Serial.println("");
    delay(250);
 Serial.println(sizeof(mcppin));
 Serial.println(mcppin[20]->getPinName());
  Serial.println (mcppin[20]->getAdresse(),HEX);
  Serial.println (mcppin[20]->getPinNummer());
  Serial.println (mcppin[20]->getPinDirection());
  Serial.println("");
    delay(250);
  Serial.println(sizeof(mcppin));
  Serial.println(mcppin[32]->getPinName());
  Serial.println (mcppin[32]->getAdresse(),HEX);
  Serial.println (mcppin[32]->getPinNummer());
  Serial.println (mcppin[32]->getPinDirection());
  Serial.println("");
    delay(250);

  /*
  if (mcppin[33]->readMCPPin())
  {
    Serial.println(mcppin[33]->readMCPPin());
    delay(250);
  }
  */
  // mcppin[0]->writeMCPPin(0,0);#
  for (int i = 0; i < 32; i++)
  {
    //mcp.digitalWrite(i, HIGH);
    mcppin[i]->writeMCPPin(HIGH);

    digitalWrite(ledPin, HIGH);
  }
  delay(1000);
  //mcppin[0]->writeMCPPin(0,1);
  for (int i = 0; i < 32; i++)
  {
    //mcp.digitalWrite(i, LOW);
    //mcp1->digitalWrite(i,LOW);

    mcppin[i]->writeMCPPin(LOW);

    digitalWrite(ledPin, LOW);
  }
  delay(1000);
}