

#include <Arduino.h>
#include <Stellpult.h>









void setup()
{
  Serial.begin(9600);
 

if (!Stellpult().begin()){
  Serial.println ("Error beim MCP definieren in Stellpult");

}
  // configure pin for output
  // mcp.pinMode(LED_PIN, OUTPUT);

  Serial.println("Looping...");

  
}


void loop()
{
  Serial.println("Auswerten");



  delay(550);
  Stellpult().WEICHE1 = (bool)false;
   Stellpult().WEICHE2 = false;
   Stellpult().WEICHE3 = false;
   Stellpult().WEICHE4 = false;
   Stellpult().WEICHE5 = true;
   Stellpult().WEICHE6 = false;
   Stellpult().WEICHE7 = false;

  Stellpult().mcpauswerten();

  delay(550);
   Stellpult().WEICHE5 = false;
   Stellpult().WEICHE6 = true;
   Stellpult().WEICHE7 = true;

  Stellpult().mcpauswerten();
  /*
  for (int gpio = 8; gpio < MAXGPIO; gpio++)
  {
    Serial.println(gpio);

    mcp[1].digitalWrite(gpio, HIGH);
    delay(1000);
  }
  delay(550);

  for (int gpio = 8; gpio < MAXGPIO; gpio++)
  {
    Serial.println(gpio);

    mcp[1].digitalWrite(gpio, LOW);
    delay(1000);
  }
  */
}