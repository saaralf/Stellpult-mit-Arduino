#include <Weiche.h>

Weiche::Weiche()
{
    setRichtung(false);
    
}

Weiche::Weiche(const int Name, const bool richtung){
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
    if (richtung){
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
   this-> name = neuername;
}
int Weiche::getName() const
{
    return name;
}