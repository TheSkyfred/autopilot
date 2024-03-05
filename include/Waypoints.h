#ifndef WAYPOINTS_H_
#define WAYPOINTS_H_



// Définir la structure pour représenter un waypoint
struct Point3D {
  float latitude;
  float longitude;
  float altitude;
};

// Définir les waypoints
extern Point3D waypoint[8];




// Définir les variables pour les waypoints actuels et suivants
extern Point3D currentWaypoint;
extern Point3D nextWaypoint;

// Déclarer la fonction pour mettre à jour les waypoints
void updateWaypoints();


#endif /* WAYPOINTS_H_ */