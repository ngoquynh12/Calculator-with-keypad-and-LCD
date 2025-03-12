#ifndef MAIN_H
#define MAIN_H

#include <16F877A.h>
#device ADC=16

// C?u hình LCD
#define LCD_ENABLE_PIN  PIN_C0
#define LCD_RS_PIN      PIN_C1
#define LCD_RW_PIN      PIN_C2
#define LCD_DATA4       PIN_C4
#define LCD_DATA5       PIN_C5
#define LCD_DATA6       PIN_C6
#define LCD_DATA7       PIN_C7 

#FUSES HS, NOWDT, NOBROWNOUT, NOLVP
#use delay(crystal=20000000)
#include <LCD.C>

// Hi?n th? ký t? lên LCD
void display_key(char key) {
    lcd_gotoxy(1, 8); // Hi?n th? t?i c?t 8 dòng 1
    lcd_putc(key);
}

#endif

