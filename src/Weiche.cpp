#include <Weiche.h>

Weiche::Weiche()
{
    setRichtung(false);
    setName("Weiche ohne Namen");
    Serial.println("Weiche angelegt");
}

Weiche::Weiche(const String Name, const bool richtung){
    Weiche();
    setName(Name);
    setRichtung(richtung);
}
Weiche::~Weiche() {}

void Weiche::setRichtung(bool neuerichtung)
{
    this->richtung = neuerichtung;
}

bool Weiche::getRichtung() const
{
    return richtung;
}
void Weiche::setName(String neuername)
{
   this-> name = neuername;
}
String Weiche::getName() const
{
    return name;
}