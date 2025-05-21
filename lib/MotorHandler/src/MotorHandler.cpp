#include <MotorHandler.h>

const int enA = 10;
const int in1 = 12;
const int in2 = 7;
const int in3 = 8;
const int in4 = 9;
const int enB = 11;

void MotorDriver_Init(void){
    for(int i=7;i<13;i++){
        pinMode(i, OUTPUT);
        pinMode(i, LOW);
    }
}

void MotorA_Write(int speed){
    if (speed > 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
      } 
      else if (speed < 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
      }
      else { // Stop if speed = 0
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
      }
      analogWrite(enA, abs(speed));
}

void MotorB_Write(int speed){
    if (speed > 0) {
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      } 
      else if (speed < 0) {
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      }
      else { // Stop if speed = 0
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
      }
      analogWrite(enB, abs(speed));
}