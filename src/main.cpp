#include <Arduino.h>
#include "def.h"
#include "Sensors.h"
#include "LEDNBuzzer.cpp"




// put function declarations here:

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  tonetest();
  Sensors_init();


}

void loop()
{
  Sensors_update();
}

// put function definitions here:

