//THIS FILE IS FOR WAYPOINT MANAGEMENT

#include "def.h"
#include "Waypoints.h"


// Définir les waypoints
Point3D waypoint[8] = {
{40.000, -105.000, 0.0},  //waypoint0 TAKEOFF
{40.100, -105.100, 100.0}, //waypoint1
{40.200, -105.200, 150.0},//waypoint2
{40.300, -105.300, 200.0},//waypoint3
{40.400, -105.400, 250.0},//waypoint4
{40.500, -105.500, 300.0},//waypoint5
{40.600, -105.600, 350.0},//waypoint6 APPROACH
{40.700, -105.700, 400.0},//waypoint7 LANDING
};



// Définir les variables pour les waypoints actuels et suivants
Point3D currentWaypoint = waypoint[0];
Point3D nextWaypoint = waypoint[1];

// Fonction pour mettre à jour les waypoints
void updateWaypoints() {

     if ( BAT_LOW == 1 ) { //condition pour aller directement à l'approche
      nextWaypoint = waypoint[6]; //GOTOApproach WE HAVE TO THINK TO ANOTHER SOLUTION
     }

  // Vérifier si le prochain waypoint est atteint (votre condition ici)
  else { //condition d'atteinte du waypoint

    // Mettre à jour les waypoints
    currentWaypoint = nextWaypoint;

    // Déterminer le prochain waypoint en fonction de la logique de votre application
    int i = 0; // Variable d'itération

    while (i < 7) {
      if (currentWaypoint.latitude == waypoint[i].latitude &&
          currentWaypoint.longitude == waypoint[i].longitude &&
          currentWaypoint.altitude == waypoint[i].altitude) {
        nextWaypoint = waypoint[i + 1];
        break;  // Sortir de la boucle dès qu'on trouve le waypoint actuel
      }
      i++;
    }
  }
}



