#include <LCDHandler.h>

uint32_t stateDuration;
LiquidCrystal lcd(A0, A1, 5, 4, 3, 2);
const uint8_t contrastPin = 6;
char buffer[16];

void LCD_Init(void){
    pinMode(contrastPin, OUTPUT);
    analogWrite(contrastPin, 100);
    lcd.begin(16,2);
}

void LCD_StateUpdate(const char* STATE_NAME){
    stateDuration = millis();
    lcd.setCursor(0,0);
    lcd.print("STATE: ");
    lcd.setCursor(8,0);
    lcd.print(STATE_NAME);
}

void LCD_StateDuration(void){
    lcd.setCursor(0,1);
    lcd.print("TIME : ");
    dtostrf((millis()-stateDuration)/1000, 3, 0, buffer);
    lcd.setCursor(8,1);
    lcd.print(buffer);
    lcd.print("s");
}

void LCD_Print(const int cursorX, const int cursorY, const char* message){
    lcd.setCursor(cursorX, cursorY);
    lcd.print(message);
}