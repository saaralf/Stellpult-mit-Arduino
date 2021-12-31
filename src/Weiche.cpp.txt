#include <Weiche.h>
#include <Adafruit_MCP23X17.h>

Weiche::Weiche()
{
    setRichtung(false);
}

Weiche::Weiche(const int Name, const bool richtung)
{
    Weiche();
    setName(Name);
    setRichtung(richtung);
}
Weiche::~Weiche() {}

void Weiche::setRichtung(bool neuerichtung)
{
    this->richtung = neuerichtung;
}

String Weiche::getRichtungText() const
{
    if (richtung)
    {
        return "Abzweig";
    }
    else
    {
        return "Gerade";
    }
}

bool Weiche::getRichtung() const
{

    return richtung;
}
void Weiche::setName(int neuername)
{
    this->name = neuername;
}
int Weiche::getName() const
{
    return name;
}
void Weiche::setTaster(const Adafruit_MCP23X17 *mcp, const unsigned int gpiopin)
{
    *mcp_device = *mcp;
    gpio_pin = gpiopin;
}
Adafruit_MCP23X17 Weiche::getTasterMCP() const
{
    return *mcp_device;
}
unsigned int Weiche::getTasterMCPpin() const
{
    return gpio_pin;
}