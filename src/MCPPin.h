#include <Arduino.h>

#include <Adafruit_MCP23X17.h>



class MCPPin
{

private:
    static unsigned int internpinNummer; // Hat einen Pinnummer 1- 128 besteht aus Adresse * 100 + Pin 0 - 15

    Adafruit_MCP23X17 &m_mcp;

public:
    int pinAdresse;        // Hat eine Adresse
    int pinStatus = LOW;   // LOW oder HIGH
    int PinDirection = -1; // INPUT oder OUTPUT

    MCPPin(Adafruit_MCP23X17 &m_mcp);

    void begin(Adafruit_MCP23X17 &mcp, int arg_mcpadresse);

    void setPinDirection(int PinDirection);
    int getPinDirection();

 
    unsigned int getPinNummer();

    void digitalWrite(int value);
    int digitalRead();
};
