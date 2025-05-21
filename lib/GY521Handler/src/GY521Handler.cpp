#include "GY521Handler.h"

MPU6050 mpu(Wire);

byte GY521_Init(void) {
  Wire.begin();
  
  // Initialize MPU6050
  byte status = mpu.begin(0, 0);
  if (status == 0) {
    delay(1000);    
    // Calibrate gyroscope and accelerometer
    mpu.calcOffsets(); // Calibrate both gyro and accel
    return 1;
  } else {
    return 0;
  }
  delay(1000);    
  // Calibrate gyroscope and accelerometer
  mpu.calcOffsets(); // Calibrate both gyro and accel
}

void GY521_Update(void) {
    mpu.update();
}

float GY521_GetAngleX(void) {
    return mpu.getAngleX(); // Return X-axis angle
}

float GY521_GetAngleY(void) {
    return mpu.getAngleY(); // Return Y-axis angle
}

float GY521_GetAngleZ(void) {
    return mpu.getAngleZ(); // Return Z-axis angle
}