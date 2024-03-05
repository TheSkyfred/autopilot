//THIS FILE IS FOR LCD SCREEN

#include "LCD.h"
#include "def.h"

void LCD_init() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 00);
  display.println("LCD READY");
  display.display();
}


void LCD_update(){
  display.setTextSize(1);
  display.setCursor(0, 00);
  display.print("BMP-Temp:");
  display.print(BMP_temp);
  display.print("C");


  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print("BMP-Altitude:");
  display.print(BMP_alt);
  display.print("m");

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("GPS-Speed:");
  display.print(GPS_speed);
  display.print("km/h");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("GPS-LAT:");
  display.print(GPS_lat);

  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("GPS-LONG:");
  display.print(GPS_lng);

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("GPS-alt2:");
  display.print(GPS_alt);
  display.print("m");

  display.display();
  delay(500);
};