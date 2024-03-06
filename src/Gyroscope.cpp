// THIS FILE IS FOR GYROSCOPE

#include "Gyroscope.h"

Adafruit_MPU6050 mpu;

void Gyroscope_init()
{
  // Try to initialize!
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  delay(10);
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 CALIBRATED");
};

void Gyroscope_update()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
};
