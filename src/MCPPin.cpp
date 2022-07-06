#include <MCPPin.h>

unsigned int MCPPin::internpinNummer=0;

MCPPin::MCPPin(Adafruit_MCP23X17 &mcp) : m_mcp(mcp)

{
}

void MCPPin::begin(Adafruit_MCP23X17 &mcp, int arg_mcpadresse)
{

    pinAdresse = arg_mcpadresse;
    internpinNummer++;
}

int MCPPin::digitalRead()
{

    return m_mcp.digitalRead(getPinNummer());
}
void MCPPin::digitalWrite(int value)
{

    m_mcp.digitalWrite(internpinNummer, value);
}
unsigned int MCPPin::getPinNummer()
{
    return internpinNummer;
}

void MCPPin::setPinDirection(int PinDirection)
{
    this->PinDirection = PinDirection;
    m_mcp.pinMode(internpinNummer, PinDirection);
}

int MCPPin::getPinDirection()
{
    return PinDirection;
}


