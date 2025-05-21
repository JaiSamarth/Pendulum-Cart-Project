#include <LEDHandler.h>

const uint8_t ledPin = 13;

void LED_Init(void){
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

void LED_Toggle(void){
    digitalWrite(ledPin, !digitalRead(ledPin));
}

void LED_Off(void){
    digitalWrite(ledPin, LOW);
}

void LED_Onn(void){
    digitalWrite(ledPin, HIGH);
}