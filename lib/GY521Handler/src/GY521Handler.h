#ifndef GY521_HANDLER
#define GY521_HANDLER

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

byte GY521_Init(void);
void GY521_Update(void);
float GY521_GetAngleX(void);
float GY521_GetAngleY(void);
float GY521_GetAngleZ(void);

#endif