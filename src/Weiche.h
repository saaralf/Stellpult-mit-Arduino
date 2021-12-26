
#include <Arduino.h>

#ifndef __CLASSWEICHE__
#define __CLASSWEICHE__

class Weiche
{
public:
    Weiche();                                    // constructor
    Weiche(const int Name, const bool richtung); // constructor

    ~Weiche();

    //void setPinMode(const unsigned int GPIO, const unsigned int richtung);
    //void setPinMode(const unsigned int GPIO, const unsigned int richtung, const bool PULLUP);
    bool getRichtung() const;
    void setRichtung(bool neuRichtung);
    void setName(int name);
    int getName() const;
    String getRichtungText() const;
    void setTaster(const Adafruit_MCP23X17 *mcp, const unsigned int gpiopin);
    Adafruit_MCP23X17 getTasterMCP() const; // gibt die Nummer des MCP
    unsigned int getTasterMCPpin() const;

private:
    bool richtung = false; // false für gerade, true = abzweig
    int name;
    unsigned int gpio_pin; // GPIO Pin des MCP23017 der die Taste für die Weiche präsentiert
    Adafruit_MCP23X17 *mcp_device; // Adresse des MCP23017

protected:
};

#endif