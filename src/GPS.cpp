// THIS FILE IS FOR THE GPS SENSOR

#include "GPS.h"
#include <TinyGPSPlus.h>

#define GPS_BAUDRATE 9600 // The default baudrate of NEO-6M is 9600

// The TinyGPSPlus object
TinyGPSPlus gps;

// Variables :
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;



void GPS_init()
{

  Serial2.begin(GPSBaud);
}

void GPS_update()
{

  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial2.available())
    {
      if (gps.encode(Serial2.read()))
      {
        newData = true;
      }
    }
  }

  // reading gps data and sending to reciever
  if (newData == true)
  {
    newData = false;
    Serial.println(gps.satellites.value());
    unsigned long GPS_speed = gps.speed.kmph();
    unsigned long GPS_sat = gps.satellites.value();
    unsigned long GPS_alt = gps.altitude.meters();
    unsigned long GPS_lat = gps.location.lat();
    unsigned long GPS_lgn = gps.location.lng();
  }
}

/*
//FUNCTIONS :

// Fonction pour vérifier si l'avion est proche d'un point GPS donné
bool isNearGPSPoint(double currentLat, double currentLon, GPSPoint targetPoint, double thresholdDistance) {
  double distance = getDistance(currentLat, currentLon, targetPoint.latitude, targetPoint.longitude);
  return distance <= thresholdDistance;
}




// Fonction pour calculer l'azimut entre deux points GPS
double calculateAzimuth(double lat1, double lon1, double lat2, double lon2) {
  // À remplacer par une formule de calcul d'azimut appropriée
  // Par exemple, utilisez la fonction atan2 dans la bibliothèque Math.h
  // Pour plus de précision, vous pourriez utiliser une bibliothèque GPS existante.
  double deltaLon = lon2 - lon1;
  double y = sin(deltaLon) * cos(lat2);
  double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(deltaLon);
  return atan2(y, x);
}

void Distanceto_NextWayPoint(){
  unsigned long Distanceto_NextWayPoint =
    (unsigned long)TinyGPSPlus::distanceBetween(
        gps.location.lat(),
        gps.location.lng(),
        nextwaypoint.lat,
        nextwaypoint.lng);
//	printInt(Distanceto_NextWayPoint, gps.location.isValid(), 9);

}

void Courseto_NextWayPoint(){
  double Courseto_NextWayPoint =
    TinyGPSPlus::courseTo(
        gps.location.lat(),
        gps.location.lng(),
        nextwaypoint.lat,
        nextwaypoint.lng);

  //printFloat(Courseto_NextWayPoint, gps.location.isValid(), 7, 2);

}

*/