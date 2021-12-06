

#include <Arduino.h>
#include <Stellpult.h>

Stellpult stellpult;
void setup()
{
  Serial.begin(9600);

  // configure pin for output
  // mcp.pinMode(LED_PIN, OUTPUT);

  Serial.println("Looping...");
}

void loop()
{
  Serial.println("Auswerten");
  stellpult.mcp[0].digitalWrite(LED2, HIGH);

  delay(550);
  stellpult.WEICHE1 = false;
  stellpult.WEICHE2 = false;
  stellpult.WEICHE3 = false;
  stellpult.WEICHE4 = false;
  stellpult.WEICHE5 = true;
  stellpult.WEICHE6 = false;
  stellpult.WEICHE7 = false;

  stellpult.mcpauswerten();

  delay(550);
  stellpult.WEICHE5 = false;
  stellpult.WEICHE6 = true;
  stellpult.WEICHE7 = true;

  stellpult.mcpauswerten();
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