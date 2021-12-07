#include <Adafruit_MCP23X17.h>



#ifndef __CLASSMCP__
#define __CLASSMCP__
#define MAXLEDMCP 2

#define MAXGPIO 16
#define MCP1ADDR 0x20
#define MCP2ADDR 0x21
#define MCP3ADDR 0x22
#define MCP4ADDR 0x23
#define MCP5ADDR 0x24
#define MCP6ADDR 0x25
#define MCP7ADDR 0x26
#define MCP8ADDR 0x27
class MCP : public Adafruit_MCP23X17
{
public:
    MCP( const int maxmcps); // constructor
    ~MCP();

    //void setPinMode(const unsigned int GPIO, const unsigned int richtung);
    //void setPinMode(const unsigned int GPIO, const unsigned int richtung, const bool PULLUP);
    Adafruit_MCP23X17 getMCP(int index);
    bool initMCP(const unsigned int  MCPADR);

private:
    Adafruit_MCP23X17 mcp23017;

protected:
};
#endif