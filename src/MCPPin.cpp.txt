#include <MCPPin.h>

MCPPin::MCPPin(Adafruit_MCP23X17 *arg_mcp, int arg_mcpadresse, int arg_pinnummer)
{

    mcp = *arg_mcp;
    pinadresse = mcp->getDevice_address();

    if (pinadresse != arg_mcpadresse)
    {
        Serial.println("Falsche Adresse, passt nicht zum MCP Chip!");
    }
    else if
    {

        pinnummer = pinadresse * 100 + arg_pinnummer;
    }
}

char MCPPin::getPinName(int pin)
{
    return mcppinname[pin];
}

void MCPPin::setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity)
{

    *mcp.setupInterrupts(mirroring, openDrain, polarity);
}
// Pinmode = INPUT, OUTPUT
void MCPPin::setPinMode(int pinmode)
{

    // Alle Pins an LED MCP auf OUTPUT
    *mcp.pinMode(pinnummer, pinmode);

    // Mode = HIGH oder LOW
    void MCPPin::setupInterruptPin(int mode)
    {

        *mcp.setupInterruptPin(pinnummer, mode);
    }
}
