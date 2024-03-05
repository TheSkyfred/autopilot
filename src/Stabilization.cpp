  
  void MPU_init(){

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //Serial.println("");
  delay(10);
  }



  CODE FROM INTERNET : 

  

// ROULIS ROLL
// TANGAGE PITCH
//LACET  YAW


unsigned long  counter_1,counter_2,  counter_6, current_count; 


//initial value 1000
float input_modeval=1000;//for channel 6 input

Servo Pitchservo;
Servo Rollservo;
float s=0;
float t=0;



Adafruit_MPU6050 mpu;
SimpleKalmanFilter xKalmanFilter(0.1, 0.01, 0.02); //pitch
SimpleKalmanFilter yKalmanFilter(0.1, 0.01, 0.02); //roll
SimpleKalmanFilter zKalmanFilter(0.1, 0.01, 0.02); //roll

int servoPitch = 7; 
int servoRoll = 8;// Pin number for the servo
int angle;  // Variable to store the servo angle
int gyro_pitch_input;
int gyro_roll_input;// Variable to store the gyro pitch input
int acc_pitch_input;
int acc_roll_input;// Variable to store the accelerometer pitch input
int pitch_output;
int roll_output;// Variable to store the final pitch control output
int Kp = 4;  // Proportional gain for the pitch control
int Kd = 2;  // Derivative gain for the pitch control
int prev_errorp = 0;
int prev_errorr = 0;


void setup() {
;
  Pitchservo.attach(servoPitch);
  Rollservo.attach(servoRoll);
Pitchservo.write(0);
Rollservo.write(90); 
pinMode(RECEIVER_PIN, INPUT);
pinMode(RECEIVER_PIN11, INPUT);  
  while (!Serial) { 
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }


  
}

void loop() { 



  switch ((input_modeval>1500))//output of the channel 5
    {
      case 0: //normal mode
      
input_modeval = pulseIn(RECEIVER_PIN, HIGH, 20000);



      if ((input_modeval > 1200 && input_modeval < 1800)) {
         //map receiver values to servo positions
        int servoPitch_pos = map(t, 644, 2444, -90, 180);
        
        int servoRoll_pos = map(s, 644, 2444, -90, 180);
        Pitchservo.write(servoPitch_pos);
        Rollservo.write(servoRoll_pos);

      }
     

                          delay(10);

              break;
              
      case 1://auto stabilize mode
            sensors_event_t a, g, temp;
            mpu.getEvent(&a, &g, &temp);
            
            float estimated_x = xKalmanFilter.updateEstimate(a.acceleration.x);
            float estimated_y = yKalmanFilter.updateEstimate(a.acceleration.y);
            float estimated_z = zKalmanFilter.updateEstimate(a.acceleration.z);
            
            
            acc_pitch_input = atan2(estimated_y, estimated_z) * 180 / PI;
            acc_roll_input = atan2(estimated_x, estimated_z) * 180 / PI;
            // Calculate the pitch angle rate using the gyro
            gyro_pitch_input = g.gyro.y / 131.0;
            gyro_roll_input = g.gyro.x / 131.0;
            
            // Calculate the error between the desired angle and the current angle
            int errorp = acc_pitch_input - gyro_pitch_input;
            int errorr = acc_roll_input - gyro_roll_input;
            // Calculate the derivative of the error
            int d_errorp = errorp - prev_errorp;
            int d_errorr = errorr - prev_errorr;
            
            // Store the current error as the previous error for the next iteration
            prev_errorp = errorp;
            prev_errorr = errorr;
            pitch_output = Kp * errorp + Kd * d_errorp;
            roll_output = Kp * errorr + Kd * d_errorr;
            // Limit the pitch control output to the range of the servo
            pitch_output = map(pitch_output,-90, 90, 0, 90);
            roll_output = map(roll_output,-90, 90, 0, 90);
            // Set the servo angle to the final pitch control output
            
            Pitchservo.write(pitch_output);
            Rollservo.write(roll_output);
             
    delay(10);
              break; 
    }
                               //delay(10);

}
