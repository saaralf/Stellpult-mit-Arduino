#include <MCPPin.h>
MCPPin::MCPPin() {}
MCPPin::MCPPin(MCP23017 &arg_mcp, int arg_mcpadresse, int arg_pinnummer)
{

    this->mcp = &arg_mcp;
    setAdresse(arg_mcpadresse);
    setPinNummer(arg_pinnummer);
}

MCPPin::~MCPPin()
{

    delete &mcp;
}

void MCPPin::setInternPinNummer()
{

    //(pinnummer - adresse * 100) % 16;
    internpinnummer = (pinNummer - getAdresse() * 100) % 16; // Sollte immer >0 <16 sein
                                                             // Serial.println(internpinnummer);
}

int MCPPin::getInternPinNummer()
{
    return internpinnummer;
}




void MCPPin::digitalWrite(int value)
{
    if (getInternPinNummer() < 8)
    {
        if (DEBUG){
        Serial.println("<8");
        MCP_PORT port = B;
        Serial.print(getPinName());
        Serial.print(": Schreibe ");
        Serial.print((value == 0) ? "LOW" : "HIGH");
        Serial.print(" Port:  ");
        Serial.print("B");
        Serial.print(" Pin:  ");
        Serial.println(getInternPinNummer());
        }
        mcp->setPin(getInternPinNummer(), B, value);
    }
    if (getInternPinNummer() > 7)
    {
        if (DEBUG){
        MCP_PORT port = A;
        Serial.print("Schreibe ");
        Serial.print((value == 0) ? "LOW" : "HIGH");
        Serial.print(" Port:  ");
        Serial.print("A");

        Serial.print(" Pin:  ");
        Serial.println((getInternPinNummer() - 8));
        }
        mcp->setPin((getInternPinNummer() - 8), A, value);
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
    mcp->setPinMode((getInternPinNummer() < 8 ? getInternPinNummer() : (getInternPinNummer() - 8)), getPort(), PinDirection);
    //this->mcp.pinMode(getInternPinNummer(), PinDirection); // DEFAULT OUTPUT
   if (DEBUG){
    Serial.print("MCPPin Name: ");
    Serial.print(getPinName());
    Serial.print(" MCPPin Nummer: ");
    Serial.print(pinNummer);
    Serial.print(" PinNummer: ");
    Serial.print((getInternPinNummer() < 8 ? getInternPinNummer() : (getInternPinNummer() - 8)));
    Serial.print(" Port: ");
    Serial.print(getPort());
    Serial.print(" Direction: ");
    Serial.println((PinDirection == 0) ? "INPUT" : "OUTPUT");
   }
}

int MCPPin::getPinDirection()
{
    return PinDirection;
}
MCP_PORT MCPPin::getPort()
{
    return (getInternPinNummer() < 8) ? B : A;
}
bool MCPPin::isINPUT()
{
    return getPinDirection() == INPUT;
}

String MCPPin::getPinDirectionName()
{
    if (getPinDirection() == 0)
    {
        return "INPUT";
    }
    if (getPinDirection() == 1)
    {
        return "OUTPUT";
    }

    return "Nicht definiert";
}

String MCPPin::getPinName()
{
    if (getInternPinNummer() < 8)
    {
        return String(getAdresse(), HEX) + "->GPB" + String(getInternPinNummer(), DEC) + "-> Direction: " + String(getPinDirectionName());
    }
    else
    {
        return String(getAdresse(), HEX) + "->GPA" + String((getInternPinNummer()) - 8, DEC) + "-> Direction: " + String(getPinDirectionName());
    }
}
void MCPPin::setPinNummer(int arg_pinnummer)
{
    pinNummer = getAdresse() * 100 + arg_pinnummer; // Adresse * 100 + Pinnummer (0-15)
    setInternPinNummer();
}

void MCPPin::readGPIOAB() {}