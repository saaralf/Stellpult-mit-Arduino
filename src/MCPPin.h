#include <Adafruit_MCP23X17.h>

#define MAXMCP 8
#define MAXPIN 128
#define MAXGPIO 16

#define MCPWITHINT1 4
#define MCPWITHINT2 5
#define MCPWITHINT3 6
#define MCPWITHINT4 7

class MCPPin
{

private:
    int mcp_adresses[8] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};
    int mcppin[MAXPIN];
    static char mcppinname[MAXPIN];
   
   
public:
    Adafruit_MCP23X17 *mcp = NULL;
    int pinadresse;
    int pinnummer;
    int pinstatus = LOW;
    int pinname = pinnummer;
    int pinmode=OUTPUT;

    MCPPin(Adafruit_MCP23X17 *mcp, int mcpadresse, int pinnummer);

    ~MCPPin();
    void setAdresse(int MCPAdresse);
    void setPinNummer(int pinnummer);

    void erzeugeMCPPIN();
    int readMCPPin(int pinnummer);
    void writeMCPPin(int pinnummer, int value);
    void setPinMode(int pinmode);
    static char getPinName(int pin);
    void setupInterrupts(bool mirroring, bool openDrain, uint8_t polarity);
};
