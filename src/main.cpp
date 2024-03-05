//ALL INCLUDES HERE
#include <Arduino.h>

// ALL FUNCTION DECCLARATIONS HERE

void setup() {

//SERIAL
if(DEBUG){

Serial

};

//TELEMETRY
Telemetry_init();

//SENSORS
Sensors_init();

}

void loop() {

Telemetry_Update();
Sensors_Update(); 

switch (MODE) {

//Initializing -> Takeoff -> Flying -> Landing

case #1

case #2


//...



}

//ALL FUNCTIONS DEFINITIONS HERE