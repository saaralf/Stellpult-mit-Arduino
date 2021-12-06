#include <MCP.h>
Adafruit_MCP23X17 mcp;

MCP::MCP()
{
}
bool MCP::initMCP(int MCPADR)
{

    if (!mcp.begin_I2C(MCPADR))
    {
        //if (!mcp.begin_SPI(CS_PIN)) {
        Serial.print("Error beim inistialisieren vom MCP mit der Adresse: ");
        Serial.println(MCPADR);
        while (1)
            return false;
    }
    return true;
}
void MCP::setPinMode(int GPIO, int richtung)
{
    if ((GPIO >= 0 && GPIO < MAXGPIO) && (richtung >=0 && richtung<2))
    {
        if (richtung == 1)
        {
            mcp.pinMode(GPIO, OUTPUT);
        }
        else
        {
        mcp.pinMode(GPIO, INPUT);

        }
    }
}
void MCP::setPinMode(int GPIO, int richtung, bool PULLUP)
{
    if ((GPIO >= 0 && GPIO < MAXGPIO) && (richtung ==0 ) && PULLUP)
    {
        if (richtung == 1)
        {
            mcp.pinMode(GPIO, INPUT_PULLUP);
        }
        else
        {
        //tue nichts
        }
    }
}