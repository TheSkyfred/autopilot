// THIS FILE IS FOR TELEMETRY

#include "def.h"
#include "Telemetry.h"
#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>
#include <SPI.h>

//Fill the MAC adress of the reciever board
uint8_t RxMACaddress[] = { 0x7C, 0x9E, 0xBD, 0xD9, 0xA0, 0xFD };

void Telemetry_init(){
  WiFi.mode(WIFI_STA);
  //------------------------------------------------------------------------------------
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //-------------------------------------------------------------------------------------
  esp_now_register_send_cb(OnDataSent);
  //-------------------------------------------------------------------------------------
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, RxMACaddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  //-------------------------------------------------------------------------------------
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
};

void Telemetry_update(){


  //-------------------------------------------------------------------------------------
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *)&sentData, sizeof(sentData));
  //-------------------------------------------------------------------------------------
  if (result == ESP_OK) Serial.println("Sent with success");
  else Serial.println("Error sending the data");
  //-------------------------------------------------------------------------------------
  delay(500);

}


//-------------------------------------------------------------------------------------
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)  //callback function
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//-------------------------------------------------------------------------------------

