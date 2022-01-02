#include <MCPPin.h>
MCPPin::MCPPin() {}
MCPPin::MCPPin(const Adafruit_MCP23X17 &arg_mcp, int arg_mcpadresse, int arg_pinnummer)
{
    if (DEBUG)
    {
        Serial.println("");

        Serial.println("");
        Serial.println("");

        Serial.print("Setze MCPPIN: ");

        Serial.print(arg_pinnummer);

        Serial.print(" für MCP ");
        Serial.print(arg_mcpadresse, HEX);
    }
    this->mcp = arg_mcp;
    setAdresse(arg_mcpadresse);
    setPinNummer(arg_pinnummer);
    this->setPinDirection(OUTPUT); // DEFAULT OUTPUT
    setPinName();
    Serial.print("PinName: ");
    Serial.println(getPinName());
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

MCPPin::~MCPPin()
{

    delete &mcp;
}

void MCPPin::setInternPinNummer()
{
    if (DEBUG)
    {
        Serial.println("");

        Serial.print("Set InternalPinNummer: ");
        Serial.println(internpinnummer);
        Serial.println("(this->pinnummer-getAdresse*100)%16");
        Serial.print("(");
        Serial.print(pinNummer);
        Serial.print("-");
        Serial.print(getAdresse());
        Serial.print("*100)%16 : InternalpinNummer: = ");
    }

    //(pinnummer - adresse * 100) % 16;
    internpinnummer = (pinNummer - getAdresse() * 100) % 16; // Sollte immer >0 <16 sein
    Serial.println(internpinnummer);
}

int MCPPin::getInternPinNummer()
{
    return internpinnummer;
}

void MCPPin::setupInterrupts(bool mirroring = true, bool openDrain = false, uint8_t polarity = HIGH)
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
    Serial.print("Internummer: ");

    Serial.print(getInternPinNummer());
    Serial.print(" : Wert: ");

    Serial.println(value);

    this->mcp.digitalWrite(getInternPinNummer(), value);
    if (DEBUG)
    {
        Serial.print("MCP: ");
        Serial.print(getAdresse(), HEX);
        Serial.print(" , PIN Nummer: ");
        Serial.print(getInternPinNummer());
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
    this->mcp.pinMode(getInternPinNummer(), PinDirection); // DEFAULT OUTPUT
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
    if (getInternPinNummer() < 8)
    {
        pinname = String(getAdresse(), HEX) + "->GPB" + String(getInternPinNummer(), DEC);
    }
    else
    {
        pinname = String(getAdresse(), HEX) + "->GPA" + String((getInternPinNummer()) - 8, DEC);
    }
}
void MCPPin::setPinNummer(int arg_pinnummer)
{
    pinNummer = getAdresse() * 100 + arg_pinnummer; // Adresse * 100 + Pinnummer (0-15)
    setInternPinNummer();
}
