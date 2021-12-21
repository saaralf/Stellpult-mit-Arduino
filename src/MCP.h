#include <Adafruit_MCP23X17.h>

#ifndef __CLASSMCP__
#define __CLASSMCP__

#define MAXGPIO 16

class MCP : public Adafruit_MCP23X17
{
public:
    MCP();                                     // constructor
    MCP(const String Name, const int adresse); // constructor
    MCP( const int adresse); // constructor

    ~MCP();

    //void setPinMode(const unsigned int GPIO, const unsigned int richtung);
    //void setPinMode(const unsigned int GPIO, const unsigned int richtung, const bool PULLUP);
    String getName() const;
    void setName(String name);
    int getAdresse() const;
    void setAdresse(int adresse);

private:
    Adafruit_MCP23X17 mcp23017;
    int adresse;
    String name;

protected:
};
#endif