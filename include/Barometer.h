#ifndef BAROMETER_H_
#define BAROMETER_H_

#include <Adafruit_BMP280.h>

#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)

Adafruit_BMP280 bmp;

void Barometer_init();
void Barometer_update();


#endif /* BAROMETER_H_ */