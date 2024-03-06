#ifndef TELEMETRY_H_
#define TELEMETRY_H_


#include <esp_now.h>
#include <WiFi.h>



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
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif /* TELEMETRY_H_ */