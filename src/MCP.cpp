#include <MCP.h>

MCP::MCP(const int maxmcps)
{
    if (maxmcps > MAXLEDMCP)
    {
        Serial.println("Anzahl MCPs nicht möglich");
    }

    Adafruit_MCP23X17 mcp[MAXLEDMCP];

    for (int mcps = 0; mcps < maxmcps; mcps++)
    {
                    Serial.print("Erzeuge MCP: ");
            Serial.println(0x20+mcps, HEX);

            if (!mcp[mcps].begin_I2C(0x20+mcps))
            {
                Serial.print("Error beim inistialisieren vom MCP mit der Adresse: ");
                Serial.println(MCP1ADDR);
                while (1)
                    ;
            }
        
    }
}
bool MCP::initMCP(const unsigned int MCPADR)
{
    Serial.print("Initialisiere MCP ");

    Serial.println(MCPADR, HEX);
    if (!mcp23017.begin_I2C(MCPADR))
    {
        //if (!mcp.begin_SPI(CS_PIN)) {
        Serial.print("Error beim inistialisieren vom MCP mit der Adresse: ");
        Serial.println(MCPADR);
        while (1)
            return false;
    }
    return true;
}
/*
void MCP::setPinMode(const unsigned int GPIO, const unsigned int richtung)
{
    if ((GPIO >= 0 && GPIO < MAXGPIO) && (richtung >=0 && richtung<2))
    {
        if (richtung == 1)
        {
            mcp23017.pinMode(GPIO, OUTPUT);
        }
        else
        {
        mcp23017.pinMode(GPIO, INPUT);

        }
    }
}
void MCP::setPinMode(const unsigned int GPIO, const unsigned int richtung, const bool PULLUP)
{
    if ((GPIO >= 0 && GPIO < MAXGPIO) && (richtung ==0 ) && PULLUP)
    {
        if (richtung == 1)
        {
            mcp23017.pinMode(GPIO, INPUT_PULLUP);
        }
        else
        {
        //tue nichts
        }
    }
  
}  */