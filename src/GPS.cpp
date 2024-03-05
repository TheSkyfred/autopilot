

void GPS_init() {

    
};



// Structure pour représenter un point en 3D (latitude, longitude, altitude)
struct Point3D {
  double latitude;
  double longitude;
  double altitude;
};




// WAYPOINTS :
/*Ex :
Point3D takeoffPoint = { 40.123, -105.456, 100.0 };
Point3D wayPoint1 = { 40.234, -105.567, 150.0 };
*/

Point3D takeoffPoint = { /*latitude_takeoff*/, /*longitude_takeoff*/, /*altitude_takeoff*/ };
Point3D wayPoint1 = { /*latitude_waypoint1*/, /*longitude_waypoint1*/, /*altitude_waypoint1*/ };
Point3D wayPoint2 = { /*latitude_waypoint2*/, /*longitude_waypoint2*/, /*altitude_waypoint2*/ };
Point3D wayPoint3 = { /*latitude_waypoint3*/, /*longitude_waypoint3*/, /*altitude_waypoint3*/ };
Point3D wayPoint4 = { /*latitude_waypoint4*/, /*longitude_waypoint4*/, /*altitude_waypoint4*/ };
Point3D wayPoint5 = { /*latitude_waypoint5*/, /*longitude_waypoint5*/, /*altitude_waypoint5*/ };
Point3D approachPoint = { /*latitude_approach*/, /*longitude_approach*/, /*altitude_approach*/ };
Point3D landingPoint = { /*latitude_landing*/, /*longitude_landing*/, /*altitude_landing*/ };



GPS_Distance_to_Home //From actual position to Landing Point
GPS_distance_mission //From Takeoff point to Landing Point
GPS_distance_next_WP //From actual position to the next WP position
GPS_distance_left //how many meters from actual position do finish the mission


/*
CHATGPT : 
// Fonction pour calculer la distance euclidienne 3D entre deux points
double distance(Point3D p1, Point3D p2) {
  double deltaLat = p2.latitude - p1.latitude;
  double deltaLon = p2.longitude - p1.longitude;
  double deltaAlt = p2.altitude - p1.altitude;

  return sqrt(deltaLat * deltaLat + deltaLon * deltaLon + deltaAlt * deltaAlt);
}

// Fonction pour calculer la distance à plat entre deux points (ignorant l'altitude)
double flatDistance(Point3D p1, Point3D p2) {
  double deltaLat = p2.latitude - p1.latitude;
  double deltaLon = p2.longitude - p1.longitude;
}


  return sqrt(deltaLat * deltaLat + deltaLon * deltaLon);



  // Calculer les distances
  double flatDistanceToTakeoff = flatDistance(currentLocation, takeoffPoint);
  double flatDistanceToLanding = flatDistance(currentLocation, landingPoint);

*/

static void calculateDistanceToHome(uint32_t* dist);
static void GPS_calc_velocity(void);
static uint16_t GPS_calc_desired_speed(uint16_t max_speed, bool _slow);






void GPS_distance_mission();

void GPS_distance_next_WP();

void GPS_Distance_to_Home()



void GPS_bearing(int32_t* lat1, int32_t* lon1, int32_t* lat2, int32_t* lon2, int32_t* bearing) {
    int32_t off_x = *lon2 - *lon1;
    int32_t off_y = (*lat2 - *lat1) / GPS_scaleLonDown;

    *bearing = 9000 + atan2(-off_y, off_x) * 5729.57795f;      //Convert the output redians to 100xdeg
  if (*bearing < 0) *bearing += 36000;
}

void GPS_distance_cm(int32_t* lat1, int32_t* lon1, int32_t* lat2, int32_t* lon2, uint32_t* dist) {
    float dLat = (float) (*lat1 - *lat2);                                    // difference of latitude in 1/10 000 000 degrees
    float dLon = (float) (*lon1 - *lon2) * GPS_scaleLonDown; //x
    *dist = sqrt(sq(dLat) + sq(dLon)) * LAT_LON_TO_CM;
}

void calculateDistanceToHome(uint32_t* dist) {
	gpsDistanceToHome[LAT] = (GPS_coord[LAT] - GPS_home[LAT]) * LAT_LON_TO_CM;
	gpsDistanceToHome[LON] = (GPS_coord[LON] - GPS_home[LON]) * LAT_LON_TO_CM * GPS_scaleLonDown; //x
    *dist = sqrt(sq((float)gpsDistanceToHome[LAT]) + sq((float)gpsDistanceToHome[LON]));
}