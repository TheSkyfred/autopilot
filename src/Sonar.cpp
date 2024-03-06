// THIS FILE IS FOR SONAR SENSOR
#include "Sonar.h"
#include <Arduino.h>
#include "def.h"


long ultrason_duration;
float distance_cm;



void Sonar_init()
{
  pinMode(trig_pin, OUTPUT); // On configure le trig en output
  pinMode(echo_pin, INPUT);  // On configure l'echo en input
}

void Sonar_update()
{
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    // Créer une impulsion de 10 µs
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(TRIG_PULSE_DURATION_US);
    digitalWrite(trig_pin, LOW);

    // Renvoie le temps de propagation de l'onde (en µs)
    ultrason_duration = pulseIn(echo_pin, HIGH);

    // Calcul de la distance
    distance_cm = ultrason_duration * SOUND_SPEED / 2 * 0.0001;

    // On affiche la distance sur le port série
    Serial.print("Distance (cm): ");
    Serial.println(distance_cm);

    delay(1000);
}