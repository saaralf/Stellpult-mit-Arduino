#include <MCPPin.h>

MCPPin::MCPPin(const Adafruit_MCP23X17 &arg_mcp, int arg_mcpadresse, int arg_pinnummer)
{
    this->mcp = arg_mcp;
    this->pinAdresse = arg_mcpadresse;
    this->pinNummer = arg_mcpadresse * 100 + arg_pinnummer; // Adresse * 100 + Pinnummer (0-15)

    this->setPinDirection(OUTPUT); //DEFAULT OUTPUT
    setPinName();

    if (DEBUG)
    {
        Serial.print("MCP: ");
        Serial.print(getAdresse(), HEX);
        Serial.print(" , PIN Nummer: ");
        Serial.print(getPinNummer());
                Serial.print(" , PIN Nummer zusammengebaut: ");

                Serial.print(pinNummer);

        Serial.print(" mit Name ");
        Serial.print(getPinName());
        Serial.println(" angelegt!");
    }

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
    Serial.print(getPinNummer());
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
    
    if (pinNummer - getAdresse() * 100 > 15)
    {
        return (pinNummer - 16) - getAdresse() * 100;
    }
    else if(pinNummer - getAdresse() * 100 > 32)
      {
        return (pinNummer - 32) - getAdresse() * 100;
    }else if(pinNummer - getAdresse() * 100 > 48)
      {
        return (pinNummer - 48) - getAdresse() * 100;
    }else if(pinNummer - getAdresse() * 100 > 60)
      {
        return (pinNummer - 60) - getAdresse() * 100;
    }else if (pinNummer - getAdresse() * 100 > 76)
      {
        return (pinNummer - 76) - getAdresse() * 100;
    }else if(pinNummer - getAdresse() * 100 >92)
      {
        return (pinNummer - 92) - getAdresse() * 100;
    }else if(pinNummer - getAdresse() * 100 > 108)
      {
        return (pinNummer - 108) - getAdresse() * 100;
    }else
    {
        return (pinNummer)-getAdresse() * 100;
    }
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
String MCPPin::getPinName()
{
    return pinname;
}
void MCPPin::setPinName()
{
    if (getPinNummer() < 8)
    {
        pinname = String (getAdresse(),HEX) + "->GPB" + String(getPinNummer(),DEC);
    }
    else
    {
        pinname = String (getAdresse(),HEX)+"->GPA" + String(getPinNummer()-8,DEC);
    }
}