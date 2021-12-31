#include <WeichenTaster.h>

WeichenTaster::WeichenTaster(const MCPPin &arg_mcppin)
{

    mcppin = arg_mcppin;
}
bool WeichenTaster::getGedrueckt()
{
    return gedrueckt;
}
void WeichenTaster::setGedrueckt(bool arg_gedrueckt)
{

    gedrueckt = arg_gedrueckt;
}
bool WeichenTaster::addWeiche(const Weiche &arg_weiche)
{
    if (!hasWeiche)
    {
        weiche = arg_weiche;
        return true;
    }

    return false;
}
int WeichenTaster::isPressed()
{
    int pin = mcppin.getLastInterruptPin();
}
