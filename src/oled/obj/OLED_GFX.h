#ifndef __OLED_GFX_H
#define __OLED_GFX_H

#include "OLED_Driver.h"
#include "ASCII_Font.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum  {
  FONT_5X8 = 0,
  FONT_8X16
}FONT_SIZE;


void Set_FontSize(FONT_SIZE size);
void Set_TextCoordinate(uint8_t x, uint8_t y);

void Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h);
void Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    
void Fill_Circle(int16_t x0, int16_t y0, int16_t r);
void Draw_Circle(int16_t x0, int16_t y0, int16_t r);

void Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r);
void Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    
void Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    
void print_String(uint8_t x, uint8_t y, const uint8_t *text, FONT_SIZE size);
void Display_String_5x8(uint8_t x, uint8_t y, const uint8_t *text);
void Display_String_8x16(uint8_t x, uint8_t y, const uint8_t *text);
    
void FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta);
void DrawCircle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t corner);

void Display_bmp(void);
void Display_Interface(void);

#endif
