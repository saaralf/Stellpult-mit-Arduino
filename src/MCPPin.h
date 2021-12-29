#include <Adafruit_MCP23X17.h>



class MCPPin
{

private:
    int mcp_adresses[8] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};
  
   
   
public:
    Adafruit_MCP23X17 mcp ;
    int pinadresse;
    int pinnummer;
    int pinstatus = LOW;
    int pinname = pinnummer;
    int pinmode=OUTPUT;

    MCPPin(const Adafruit_MCP23X17 &mcp, int mcpadresse, int pinnummer);

    ~MCPPin();
    void setAdresse(int MCPAdresse);
    void setPinNummer(int pinnummer);

    int readMCPPin(int pinnummer);
    void writeMCPPin(int pinnummer, int value);
    void setPinMode(int pinmode);
    static char getPinName(int pin);
    void setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity);
    int getLastInterruptPin();
};
