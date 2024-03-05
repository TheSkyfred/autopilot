//This file is for WAYPOINTS MANAGEMENT



//WAYPOINT'S COORDINATES ARE IN ANOTHER FILE 


//For each WP : Lat, Lgn, Alt

Takeoff_Point ; 
Waypoint_1;
Waypoint_2;
Waypoint_3;
Waypoint_4;
Approach_Point;
Landing_Point;


Takeoff_GPS_alt



//Fonction to calculate the tilt between the actual Current_GPS_Altitude and the Next_Waypoint_Altitude

// Convertir les coordonnées en radians
double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

// Calculer la distance euclidienne entre deux points GPS (en mètres)
double calculateDistance(const Point3D& point1, const Point3D& point2) {
    double lat1 = toRadians(point1.latitude);
    double lon1 = toRadians(point1.longitude);
    double lat2 = toRadians(point2.latitude);
    double lon2 = toRadians(point2.longitude);

    // Rayon de la Terre en mètres (approximation)
    const double radius = 6371000.0;

    // Formule de distance euclidienne
    double dx = (lon2 - lon1) * cos(0.5 * (lat2 + lat1));
    double dy = lat2 - lat1;

    return radius * sqrt(dx * dx + dy * dy);
}

// Calculer l'angle entre deux points GPS (en degrés)
double calculateAngle(const Point3D& point1, const Point3D& point2) {
    double distance = calculateDistance(point1, point2);
    double altitudeDiff = point2.altitude - point1.altitude;

    // Utiliser la trigonométrie pour calculer l'angle
    double angle = atan2(altitudeDiff, distance) * 180.0 / M_PI;

    return angle;
}

int main() {
    // Exemple d'utilisation
    Point3D pointA = { 40.123, -105.456, 100.0 };
    Point3D pointB = { 40.234, -105.567, 150.0 };

    double angle = calculateAngle(pointA, pointB);

    // Afficher l'angle
    printf("Angle entre les points A et B : %.2f degrés\n", angle);

    return 0;
}