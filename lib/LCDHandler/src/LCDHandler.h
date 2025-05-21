#ifndef LCD_HANDLER
#define LCD_HANDLER

#include <Arduino.h>
#include <LiquidCrystal.h>

void LCD_Init(void);
void LCD_StateUpdate(const char* STATE_NAME);
void LCD_StateDuration(void);
void LCD_Print(const int cursorX, const int cursorY, const char* message);

#endif