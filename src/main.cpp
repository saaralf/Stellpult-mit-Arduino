#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <MCPPin.h>

#define MCPS 2
Adafruit_MCP23X17 mcp[MCPS];

MCPPin mcppin0(mcp[0]);
MCPPin mcppin1(mcp[0]);
MCPPin mcppin2(mcp[0]);
MCPPin mcppin3(mcp[0]);
MCPPin mcppin4(mcp[0]);
MCPPin mcppin5(mcp[0]);
MCPPin mcppin6(mcp[0]);
MCPPin mcppin7(mcp[0]);
MCPPin mcppin8(mcp[0]);
MCPPin mcppin9(mcp[0]);
MCPPin mcppin10(mcp[0]);
MCPPin mcppin11(mcp[0]);
MCPPin mcppin12(mcp[0]);
MCPPin mcppin13(mcp[0]);
MCPPin mcppin14(mcp[0]);
MCPPin mcppin15(mcp[0]);
void setup()
{
  Serial.begin(115200);

  mcp[0].begin_I2C(0x20);
  mcp[1].begin_I2C(0x20);

  /*
    for (int i = 0; i < MCPS; i++)
    {
      Serial.print("MCP: ");
      Serial.println(0x20 + i, HEX);

      mcp[i].begin_I2C(0x20 + i);
    }
  */

  mcppin0.setPinDirection(OUTPUT);
  mcppin1.setPinDirection(OUTPUT);

  // MCPPin mcppin(&mcp, 0x20, 0);
  //  mcppin.begin(mcp[0], 0x20, 0);

  Serial.println("Looping...");
}

void loop()
{

  mcppin0.digitalRead();
  mcppin1.digitalRead();
}
