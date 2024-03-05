// THIS FILE IS FOR SENSORS MANAGEMENT

#include "Barometer.h"
#include "Compass.h"
#include "GPS.h"
#include "Gyroscope.h"
#include "LCD.h"
#include "Telemetry.h"
#include "Servos.h"
#include "Sonar.h"

// Initialization of all captors
void Sensors_init()
{
    GPS_init();
    Barometer_init();
    Telemetry_init();
    LCD_init();
}

void Sensors_update()
{

    static uint8_t taskOrder = 0; // never call all functions in the same loop, to avoid high delay spikes
    switch (taskOrder)
    {

    case 0:
        taskOrder++;
        GPS_update();
        break;
    case 1:
        taskOrder++;
        void Barometer_update();
        break;
    case 2:
        taskOrder++;
        void Telemetry_update();
        break;
    }
}