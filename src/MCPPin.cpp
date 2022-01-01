#include <MCPPin.h>

MCPPin::MCPPin(const Adafruit_MCP23X17 &arg_mcp, int arg_mcpadresse, int arg_pinnummer)
{
    this->mcp = arg_mcp;
    setAdresse(arg_mcpadresse);
    setPinNummer(arg_pinnummer);
    this->setPinDirection(OUTPUT); // DEFAULT OUTPUT
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

    this->setPinDirection(PinDirection); // DEFAULT OUTPUT
}

MCPPin::~MCPPin()
{

    delete &mcp;
}

void MCPPin::setInternPinNummer()
{
    //(pinnummer - adresse * 100) % 16;
    internpinnummer = (pinNummer - getAdresse() * 100) % 16; // Sollte immer >0 <16 sein
}

int MCPPin::getInternPinNummer()
{
    return internpinnummer;
}

void MCPPin::setupInterrupts(bool mirroring=true, bool openDrain=false, uint8_t polarity=HIGH)
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
    Serial.println(mcp.digitalRead(getInternPinNummer()));

    return mcp.digitalRead(getInternPinNummer());
}
void MCPPin::digitalWrite(int value)
{
    mcp.digitalWrite(getInternPinNummer(), value);
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
    return pinNummer;
}
void MCPPin::setAdresse(int arg_address)
{
    pinAdresse = arg_address;
}

int MCPPin::getAdresse()
{
    return pinAdresse;
}
void MCPPin::setPinDirection(int PinDirection)
{
    this->PinDirection = PinDirection;
    this->mcp.pinMode(getPinNummer(), PinDirection); // DEFAULT OUTPUT
    
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
        pinname = String(getAdresse(), HEX) + "->GPB" + String(getInternPinNummer(), DEC);
    }
    else
    {
        pinname = String(getAdresse(), HEX) + "->GPA" + String(getInternPinNummer() - 8, DEC);
    }
}
void MCPPin::setPinNummer(int arg_pinnummer)
{
    pinNummer = arg_pinnummer * 100 + arg_pinnummer; // Adresse * 100 + Pinnummer (0-15)
}
