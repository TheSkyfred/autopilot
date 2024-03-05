#ifndef LCD_H_
#define LCD_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);


//Functions :
void LCD_init();
void LCD_update();

#endif /* LCD_H_ */