#include <MCP.h>
MCP::MCP(const String Name, const int adresse)
{}
MCP::MCP(const int adresse)
{
    if (adresse < 0x20 || adresse > 0x27)
    {
        Serial.println("ungültige Adresse");
        return;
    }

    setAdresse(adresse);

    Serial.print("Erzeuge MCP: ");
    Serial.println(adresse, HEX);

    if (!begin_I2C(adresse))
    {
        Serial.print("Error beim inistialisieren vom MCP ");
        Serial.print(getName());
        Serial.print(" mit der Adresse: ");
        Serial.println(adresse, HEX);
        while (1)
            ;
    }
}

void MCP::setName(String name)
{
    this->name = name;
}

String MCP::getName() const
{
    return name;
}

void MCP::setAdresse(int adresse)
{
    this->adresse = adresse;
}

int MCP::getAdresse() const
{
    return adresse;
}


/*
void MCP::setPinMode(const unsigned int GPIO, const unsigned int richtung)
{
    if ((GPIO >= 0 && GPIO < MAXGPIO) && (richtung >=0 && richtung<2))
    {
        if (richtung == 1)
        {
            mcp23017.pinMode(GPIO, OUTPUT);
        }
        else
        {
        mcp23017.pinMode(GPIO, INPUT);

        }
    }
}
void MCP::setPinMode(const unsigned int GPIO, const unsigned int richtung, const bool PULLUP)
{
    if ((GPIO >= 0 && GPIO < MAXGPIO) && (richtung ==0 ) && PULLUP)
    {
        if (richtung == 1)
        {
            mcp23017.pinMode(GPIO, INPUT_PULLUP);
        }
        else
        {
        //tue nichts
        }
    }
  
}  */