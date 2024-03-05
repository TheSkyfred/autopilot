//THIS FILE IS FOR LCD SCREEN
//WE HAVE 4 SERVOS
//2 FOR WING'S fins
//1 elevator
//1 rudder

#include "Servos.h"
#include "def.h"
#include <SimpleKalmanFilter.h>
#include <Servo.h>


Servo Rollservo;
Servo Pitchservo;
Servo Yawservo;

SimpleKalmanFilter xKalmanFilter(0.1, 0.01, 0.02); //pitch
SimpleKalmanFilter yKalmanFilter(0.1, 0.01, 0.02); //roll
SimpleKalmanFilter zKalmanFilter(0.1, 0.01, 0.02); //roll


int servoPitch = 7; 
int servoRoll = 8;// Pin number for the 
int servoYaw = 7; 
int angle;  // Variable to store the servo angle
int gyro_pitch_input;
int gyro_roll_input;// Variable to store the gyro pitch input
int gyro_yaw_input
int acc_pitch_input;
int acc_roll_input;
int acc_yaw_input;// Variable to store the accelerometer pitch input
int pitch_output;
int roll_output;
int yaw_output;// Variable to store the final pitch control output
int Kp = 4;  // Proportional gain for the pitch control
int Kd = 2;  // Derivative gain for the pitch control

int prev_errorp = 0;
int prev_errorr = 0;
int prev_errory = 0;

void Servos_init(){
  Rollservo.attach(servoRoll);
  Pitchservo.attach(servoPitch);
    Rollservo.attach(servoYaw);
Pitchservo.write(0);
Rollservo.write(90); 
Yawservo.write(90); 



};


            float estimated_x = xKalmanFilter.updateEstimate(a.acceleration.x);
            float estimated_y = yKalmanFilter.updateEstimate(a.acceleration.y);
            float estimated_z = zKalmanFilter.updateEstimate(a.acceleration.z);


void Stabilization(){

 // Gyroscope_update(); //Already done by the sensors_update function
 // Compass_update(); //Already done by the sensors_update function


Pitch_stabilization();
Roll_stabilization();
Yaw_stabilization();
}

void Pitch_stabilization(){
            acc_pitch_input = atan2(estimated_y, estimated_z) * 180 / PI;
            gyro_pitch_input = g.gyro.y / 131.0;       // Calculate the pitch angle rate using the gyro
            int errorp = acc_pitch_input - gyro_pitch_input;  // Calculate the error between the desired angle and the current angle
       int d_errorp = errorp - prev_errorp;     // Calculate the derivative of the error
              prev_errorp = errorp; // Store the current error as the previous error for the next iteration
      pitch_output = Kp * errorp + Kd * d_errorp;
      
       pitch_output = map(pitch_output,-90, 90, 0, 90);   // Limit the pitch control output to the range of the servo
        Pitchservo.write(pitch_output); // Set the servo angle to the final pitch control output
      }




void Roll_stabilization(){

                       acc_roll_input = atan2(estimated_x, estimated_z) * 180 / PI;
        gyro_roll_input = g.gyro.x / 131.0;       // Calculate the pitch angle rate using the gyro

        int errorr = acc_roll_input - gyro_roll_input;
           int d_errorr = errorr - prev_errorr;
              prev_errorr = errorr;
                roll_output = Kp * errorr + Kd * d_errorr;
                 roll_output = map(roll_output,-90, 90, 0, 90);
                   Rollservo.write(roll_output);
}


void Yaw_stabilization(){   
 acc_yaw_input = atan2(estimated_z, estimated_z) * 180 / PI;
     gyro_yaw_input = g.gyro.z / 131.0;       // Calculate the pitch angle rate using the gyro
              int errory = acc_yaw_input - gyro_yaw_input;
                  int d_errory = errory - prev_errory;
                     prev_errory = errory;
      yaw_output = Kp * errory + Kd * d_errory;
  yaw_output = map(yaw_output,-90, 90, 0, 90);
      Yawservo.write(roll_output);

}
  
      
        