#include <MCPPin.h>

MCPPin::MCPPin(const Adafruit_MCP23X17 &arg_mcp, int arg_mcpadresse, int arg_pinnummer)
{
    mcp = arg_mcp;
    pinnummer = arg_mcpadresse * 100 + arg_pinnummer;
}

MCPPin::~MCPPin()
{

    delete &mcp;
}

void MCPPin::setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity)
{

    mcp.setupInterrupts(mirroring, openDrain, polarity);
}
// Pinmode = INPUT, OUTPUT
void MCPPin::setPinMode(int pinmode)
{

    // Alle Pins an LED MCP auf OUTPUT
    mcp.pinMode(pinnummer, pinmode);
}
int MCPPin::getLastInterruptPin()
{

    return mcp.getLastInterruptPin();
}
