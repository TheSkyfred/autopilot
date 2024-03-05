#ifndef TELEMETRY_H_
#define TELEMETRY_H_


#include <esp_now.h>
#include <WiFi.h>

//Fill the MAC adress of the reciever board
uint8_t RxMACaddress[] = { 0x7C, 0x9E, 0xBD, 0xD9, 0xA0, 0xFD };

//defining the data messages we want to sent to reciever
typedef struct struct_message {
 // int bat;
  float temp;
  float alt;
  float speed;
  int sat;


} struct_message;
struct_message sentData;

void Telemetry_init();
void Telemetry_update();
void OnDataSent();

#endif /* TELEMETRY_H_ */