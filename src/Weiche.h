
#include <Arduino.h>

#ifndef __CLASSWEICHE__
#define __CLASSWEICHE__

class Weiche
{
public:
    Weiche();                                       // constructor
    Weiche(const int Name, const bool richtung); // constructor

    ~Weiche();

    //void setPinMode(const unsigned int GPIO, const unsigned int richtung);
    //void setPinMode(const unsigned int GPIO, const unsigned int richtung, const bool PULLUP);
    bool getRichtung() const;
    void setRichtung(bool neuRichtung);
    void setName(int name);
    int getName() const;
    String getRichtungText() const;

private:
    bool richtung = false; // false für gerade, true = abzweig
    int name;

protected:
};

#endif