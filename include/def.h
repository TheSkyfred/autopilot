
#ifndef DEF_H_
#define DEF_H_

//Fill the MAC adress of the reciever board
uint8_t RxMACaddress[] = { 0x7C, 0x9E, 0xBD, 0xD9, 0xA0, 0xFD };



float GPS_lat;
float GPS_lng;
float GPS_speed; // kmph
int GPS_sat;
float GPS_alt; // meters

int BAT_LOW = 0;

#define SERVO_1_PINMODE \
  pinMode(XXX, OUTPUT); \
  pinMode(44, OUTPUT); // TILT_ROLL - WING
#define SERVO_1_PIN_HIGH \
  PORTC |= 1 << 3;       \
  PORTL |= 1 << 5;
#define SERVO_1_PIN_LOW \
  PORTC &= ~(1 << 3);   \
  PORTL &= ~(1 << 5);
#define SERVO_2_PINMODE \
  pinMode(35, OUTPUT);  \
  pinMode(45, OUTPUT); // TILT_PITCH  - alt TILT_PITCH
#define SERVO_2_PIN_HIGH \
  PORTC |= 1 << 2;       \
  PORTL |= 1 << 4;
#define SERVO_2_PIN_LOW \
  PORTC &= ~(1 << 2);   \
  PORTL &= ~(1 << 4);
#define SERVO_3_PINMODE \
  pinMode(33, OUTPUT);  \
  pinMode(46, OUTPUT); // TILT_YAW -
#define SERVO_3_PIN_HIGH \
  PORTC |= 1 << 4;       \
  PORTL |= 1 << 3;
#define SERVO_3_PIN_LOW \
  PORTC &= ~(1 << 4);   \
  PORTL &= ~(1 << 3);

#define BUZZER_PIN 23
#define BUZZER_CHANNEL 0

// SONAR
const int trig_pin = 5;
const int echo_pin = 18;
#define SOUND_SPEED 340
#define TRIG_PULSE_DURATION_US 10


//TELEMETRY :



#endif /* DEF_H_ */