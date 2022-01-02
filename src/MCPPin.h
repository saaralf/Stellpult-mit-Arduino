#include <Adafruit_MCP23X17.h>

class MCPPin
{

private:
    Adafruit_MCP23X17 mcp; // Benötigt eine Referenze auf einen MCP
    bool DEBUG = false;
    int internpinnummer; // Diese Nummer ist immer 0-15 und wird benötigt um mit dem MCP zu kommunizieren und errechnet sich aus der Pinnummer

public:
    int pinAdresse;            // Hat eine Adresse
    int pinNummer;             // Hat einen Pinnummer 1- 128 besteht aus Adresse * 100 + Pin 0 - 15
    int pinStatus = LOW;       // LOW oder HIGH
    int PinDirection = OUTPUT; // INPUT oder OUTPUT
    String pinname = "";
    void setInternPinNummer();
    int getInternPinNummer();
    MCPPin(const Adafruit_MCP23X17 &mcp, int mcpadresse, int pinnummer);
    MCPPin();
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
    void digitalWrite(int value);
    bool isINPUT();

    void setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity);
    int getLastInterruptPin();
};
