#ifndef MOTOR_HANDLER
#define MOTOR_HANDLER

#include <Arduino.h>

void MotorDriver_Init(void);
void MotorA_Write(int speed);
void MotorB_Write(int speed);

#endif