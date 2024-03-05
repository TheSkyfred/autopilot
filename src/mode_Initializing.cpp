//This file is for before take off

//Sensors are already initialized


case (TakeOff_TaskManager)

//1-We verify that the accuracy of the GPS is good enough


//the orientation of the plane is good for takeoff
if (current_Direction = Takeoff_Direction) {
Takeoff_compass=1;
LED1=1;
}

else {
Takeoff_compass=0;
LED1=0;
    Takeoff_Armed = 0;
}

if (current_tilt_angle = Takeoff_tilt_angle) {
Takeoff_Tilt=1;
LED2=1;

else {
    Takeoff_Tilt=0;
LED2=0;
    Takeoff_Armed = 0;
}

}

if ( Takeoff_compass = 1 && Takeoff_tilt=1) {
    Takeoff_Armed = 1;
    Takeoff_Timer = millis();
}


//From here to the and of the Takeoff procedure, if we put the plane on his back, engine off


//Here is the Takeoff procedure :

Case 0 :




//