#include <Arduino.h>
#include <MCPPin.h>
#include <Weiche.h>
#include <stdint.h>

#ifndef __WEICHENTASTER__
#define __WEICHENTASTER__

class WeichenTaster
{
public:
    MCPPin mcppin;

    WeichenTaster(const MCPPin &arg_mcppin);
    ~WeichenTaster();

    bool getGedrueckt();
    void setGedrueckt(bool arg_gedrueckt);
    bool addWeiche(const Weiche &arg_weiche);
    int isPressed();

private:
    bool gedrueckt = false; // ist gedrückt?
    Weiche weiche;
    bool hasWeiche=false;
};
#endif