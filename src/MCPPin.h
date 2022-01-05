//#include <Adafruit_MCP23X17.h>
#include <MCP23017.h>

class MCPPin
{

private:
    MCP23017 *mcp; // Benötigt eine Referenze auf einen MCP

    bool DEBUG = false;
    unsigned int  internpinnummer; // Diese Nummer ist immer 0-15 und wird benötigt um mit dem MCP zu kommunizieren und errechnet sich aus der Pinnummer
    bool ispressed = false;
    MCP_PORT port;
public:
    int pinAdresse;        // Hat eine Adresse
    unsigned int pinNummer;         // Hat einen Pinnummer 1- 128 besteht aus Adresse * 100 + Pin 0 - 15
    int pinStatus = LOW;   // LOW oder HIGH
    int PinDirection = -1; // INPUT oder OUTPUT
    String pinname = "";
    void setInternPinNummer();
    unsigned int  getInternPinNummer();
    MCPPin(MCP23017 &arg_mcp, int arg_mcpadresse, MCP_PORT port, int arg_pinnummer);
    MCPPin(MCP23017 &mcp, int mcpadresse, int pinnummer);
    MCPPin();
    ~MCPPin();
    void setAdresse(int MCPAdresse);
    int getAdresse();
    MCP_PORT getPort();
    void setPort(MCP_PORT port);

    void setPinDirection(int PinDirection);
    int getPinDirection();
    String getPinDirectionName();
    String getPinName();
    void setPinNummer(int pinnummer);
    unsigned int  getPinNummer();
    int readMCPPin();
    void digitalWrite(int value);
    bool isPressed();
    void setPressed(bool value);
    void readGPIOAB();
    void setupInterruptPin();
};