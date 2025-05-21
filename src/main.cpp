#include <Arduino.h>
#include <LEDHandler.h>
#include <LCDHandler.h>
#include <GY521Handler.h>
#include <MotorHandler.h>

//State Machine Variables
enum class pendulumState : uint8_t {IDLE, UPRIGHT, AUTOBAL};
static pendulumState currentState = pendulumState::IDLE;
static uint8_t userHolding = false;
static uint8_t failed = false;
static uint32_t uprightStartTime = 0;

//PID Variables
const float kP = 70.0f;
const float kD = 1400.0f;
const float kI = 0.08f;

//Error Tracking
float angleTarget = 0.0f;
float error = 0.0f;
float errorOld;
float errorChange;
float errorSlope = 0.0f;
float errorArea = 0.0f;
float errorFeedback;

//Timing
uint32_t milliOld;
uint32_t milliNew;
uint32_t dt;

//motor speed
int speed;
char lcdMessage[16];

void setup(){
  Serial.begin(115200);
  MotorDriver_Init();
  LED_Init();
  LCD_Init();
  LCD_StateUpdate("INIT   ");
  if (GY521_Init() == 0) {
    LCD_Print(0,0,"GYRO INI FAIL");
    while(1){}
    
  }
  LCD_StateUpdate("IDLE   ");
}

void loop(){
  static float xAngle = 0.0f;
  static float lastAngle = 0.0f;

  GY521_Update();
  xAngle = GY521_GetAngleZ();
  // //Offset
  // xAngle = xAngle+91.8;

  // //Motor testing code
  // dtostrf(xAngle, 6, 2, lcdMessage);
  // LCD_Print(0, 1, "Angle : ");  
  // LCD_Print(8, 1, lcdMessage); 
  // speed = (int)constrain(xAngle*25.0, -255,255);
  // dtostrf(speed, 6, 0, lcdMessage);
  // LCD_Print(0, 0, "Speed : ");  
  // LCD_Print(8, 0, lcdMessage); 
  // // MotorA_Write(speed);
  // // MotorB_Write(speed);

  //StateMachine
  switch (currentState){
  case pendulumState::IDLE:
    if(abs(xAngle) <= 15.f && !userHolding && !failed){
      currentState = pendulumState::UPRIGHT;
      uprightStartTime = millis();
      LED_Onn();
      LCD_StateUpdate("UPRIGHT");
    } else if (abs(xAngle) > 60.f)
    {
      userHolding = false;
      failed = false;
    }    
    break;
  
  case pendulumState::UPRIGHT:
    if(abs(xAngle - lastAngle) <= .1f){
      userHolding = true;
      if((millis() - uprightStartTime)>=5000){
        currentState = pendulumState::IDLE;
        LED_Off();
        LCD_StateUpdate("IDLE   ");
      }
    } 
    else if ((millis() - uprightStartTime)>1000){
      currentState = pendulumState::AUTOBAL;
      LCD_StateUpdate("AUTOBAL");
      milliNew = millis();
      error = 0.0f;
      errorSlope = 0.0f;
      errorArea = 0.0f;
    }    
    break;

  case pendulumState::AUTOBAL:
    if(abs(xAngle)>60.f){
      failed = true;
      MotorA_Write(0);
      MotorB_Write(0);
      LED_Off();
      LCD_StateDuration();
      currentState = pendulumState::IDLE;
      LCD_StateUpdate("IDLE   ");
    } 
    else{
      milliOld = milliNew;
      milliNew = millis();
      dt = milliNew - milliOld;
      errorOld = error;
      error = angleTarget - xAngle;
      errorChange = error - errorOld;
      errorSlope = errorChange/dt;
      errorArea += error*dt;
      errorFeedback = kP*error + kD*errorSlope + kI*errorArea;

      speed = (int)constrain(errorFeedback*50, -255,255);
      MotorA_Write(-speed);
      MotorB_Write(-speed);
      // Serial.print("currentAngle:");
      // Serial.print(xAngle);
      // Serial.print(",");
      // Serial.print("Speed:");
      // Serial.println(speed);
    }
    break;
  }
  lastAngle = xAngle;
}