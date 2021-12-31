#include <MCPPin.h>

MCPPin::MCPPin(const Adafruit_MCP23X17 &arg_mcp, int arg_mcpadresse, int arg_pinnummer)
{
    this->mcp = arg_mcp;
    this->pinAdresse = arg_mcpadresse;
    this->pinNummer = arg_mcpadresse * 100 + arg_pinnummer; // Adresse * 100 + Pinnummer (0-15)

    this->setPinDirection(OUTPUT); //DEFAULT OUTPUT
}

MCPPin::MCPPin(const Adafruit_MCP23X17 &arg_mcp, int arg_mcpadresse, int arg_pinnummer, int PinDirection)
{
    this->mcp = arg_mcp;
    this->pinAdresse = arg_mcpadresse;
    this->pinNummer = arg_mcpadresse * 100 + arg_pinnummer; // Adresse * 100 + Pinnummer (0-15)

    this->setPinDirection(PinDirection); //DEFAULT OUTPUT
}

MCPPin::~MCPPin()
{

    delete &mcp;
}

void MCPPin::setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity)
{

    mcp.setupInterrupts(mirroring, openDrain, polarity);
}

int MCPPin::getLastInterruptPin()
{

    return mcp.getLastInterruptPin();
}
int MCPPin::readMCPPin()
{
    Serial.print("Status: ");

    Serial.println(mcp.digitalRead(getPinNummer()));

    return mcp.digitalRead(getPinNummer());
}
void MCPPin::writeMCPPin(int value)
{
    mcp.digitalWrite(getPinNummer(), value);
    if (DEBUG)
    {
        Serial.print("MCP: ");
        Serial.print(getAdresse(), HEX);
        Serial.print(" , PIN Nummer: ");
        Serial.print(getPinNummer());
        Serial.print(" wird auf ");
        Serial.print(value);
        Serial.println(" geschaltet!");
    }
}
int MCPPin::getPinNummer()
{
    return pinNummer - getAdresse() * 100;
}
int MCPPin::getAdresse()
{
    return pinAdresse;
}
void MCPPin::setPinDirection(int PinDirection)
{
    this->PinDirection = PinDirection;
    this->mcp.pinMode(getPinNummer(), PinDirection); //DEFAULT OUTPUT
}
int MCPPin::getPinDirection()
{
    return PinDirection;
}

bool MCPPin::isINPUT()
{
    return getPinDirection() == INPUT;
}
