#include <Adafruit_MCP23X17.h>

class MCPPin
{

private:
    Adafruit_MCP23X17 mcp; //Benötigt eine Referenze auf einen MCP
    bool DEBUG = true;

public:
    int pinAdresse;            // Hat eine Adresse
    int pinNummer;             // Hat einen Pinnummer 1- 128 besteht aus Adresse * 100 + Pin 0 - 15
    int pinStatus = LOW;       // LOW oder HIGH
    int PinDirection = OUTPUT; // INPUT oder OUTPUT
    String pinname="";

    MCPPin(const Adafruit_MCP23X17 &mcp, int mcpadresse, int pinnummer,int PinDirection);
    MCPPin(const Adafruit_MCP23X17 &mcp, int mcpadresse, int pinnummer);

    ~MCPPin();
    void setAdresse(int MCPAdresse);
    int getAdresse();
    void setPinDirection(int PinDirection);
    int getPinDirection();
    void setPinName();
    String getPinName();
    void setPinNummer(int pinnummer);
    int getPinNummer();
    int readMCPPin();
    void writeMCPPin(int value);
    bool isINPUT();

    void setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity);
    int getLastInterruptPin();
};
