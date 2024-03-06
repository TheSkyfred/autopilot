// THIS FILE IS FOR BMP280

#include "Barometer.h"
#include "def.h"

float BMP_temp; // BMP280 TEMPERATURE IN CELCIUS
float BMP_alt;  // BMP280 ALTITUDE IN METERS

void Barometer_init()
{

  if (!bmp.begin())
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1)
      delay(10);
  }
};

void Barometer_update()
{
  BMP_temp = bmp.readTemperature(); // reading temperature and sending to reciever

  BMP_alt = bmp.readAltitude(1013.25); // adjust barometric pressure in your location
};
