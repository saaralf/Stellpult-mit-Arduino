#include <Weiche.h>
#include <MCP23017.h>

Weiche::Weiche()
{
    setRichtung(false);
}

Weiche::Weiche( const bool richtung)
{
    Weiche();
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
