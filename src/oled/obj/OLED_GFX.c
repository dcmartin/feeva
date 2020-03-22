#include "OLED_GFX.h"
#include <stdio.h>

#define swap(a, b) { uint16_t t = a; a = b; b = t; }

uint8_t Row,Column;
FONT_SIZE Font_Size;


void OLED_GFX(void)  {
  Row = 0;
  Column = 0;
  Font_Size = FONT_5X8;
}


void Set_FontSize(FONT_SIZE size) {
  Font_Size = size;
}


void print_String(uint8_t x, uint8_t y, const uint8_t *text, FONT_SIZE size) {

  Font_Size = size;

  if(Font_Size == FONT_5X8) {
    Display_String_5x8(x, y, text);
  }
  else if(Font_Size == FONT_8X16) {
    Display_String_8x16(x, y, text);
  }
}


void Display_String_8x16(uint8_t x, uint8_t y, const uint8_t *text) {
  
  uint16_t i=0,j,k,n;
  if(x>120)  {
    x=1;
  }
  while(text[i]>0x00) {
    if((text[i]>=0x20)&&(text[i]<=0x7e))  {
      j=text[i]-0x20;
      for(n=0;n<2;n++)  {
        for(k=0;k<8;k++)  {
          Set_Address(x+k, n*8+y);
          Write_text(ascii_table_8x16[j][k+8*n]);
        }
      }
      i++;
      x+=8;
    }
    else
      i++;
  }
}


void Display_String_5x8(uint8_t x, uint8_t y, const uint8_t *text)  {
  uint8_t i=0,j,k;
  while(text[i]>0x00) {	
    if((text[i]>=0x20)&&(text[i]<=0x7e))  {
      j=text[i]-0x20;
      for(k=0; k<5;k++)  {
        Set_Address(x+k, y);
        Write_text(ascii_table_5x8[j][k]);
      }
      Set_Address(x+5, y);   
      Write_text(0x00);
      i++;
      x+=6;
      if(x>=128)
        x=1;
    }
    else  
      i++;
  }
}


void Set_TextCoordinate(uint8_t x, uint8_t y) {
  Column = x;
  Row = y;
}


void Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  // Update in subclasses if desired!
  if(x0 == x1)  {
    if(y0 > y1) swap(y0, y1);
    Draw_FastVLine(x0, y0, y1 - y0 + 1);
  } 
  else if(y0 == y1) {
    if(x0 > x1)
      swap(x0, x1);
    Draw_FastHLine(x0, y0, x1 - x0 + 1);
  }
  else
    Write_Line(x0, y0, x1, y1);
}


void Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1)  {
    
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    
  if (steep)  {
    swap(x0, y0);
    swap(x1, y1);
  }
  if (x0 > x1)  {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if(y0 < y1) {
    ystep = 1;
  } 
  else  {
    ystep = -1;
  }

  for(; x0<=x1; x0++) {
    if(steep)
      Draw_Pixel(y0, x0);
    else
      Draw_Pixel(x0, y0);
    err -= dy;
      
    if(err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


// Draw a rectangle
void Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h) {
  Draw_FastHLine(x, y, w);
  Draw_FastHLine(x, y+h-1, w);
  Draw_FastVLine(x, y, h);
  Draw_FastVLine(x+w-1, y, h);
}


/**************************************************************************/
/*!
    @brief  Draws a filled rectangle using HW acceleration
*/
/**************************************************************************/
void Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {

  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
  return;
  // Y bounds check
  if (y+h > SSD1351_HEIGHT) {
    h = SSD1351_HEIGHT - y - 1;
  }
  // X bounds check
  if (x+w > SSD1351_WIDTH)  {
    w = SSD1351_WIDTH - x - 1;
  }
  // set location
  Write_Command(SSD1351_CMD_SETCOLUMN);
  Write_Data(x);
  Write_Data(x+w-1);
  Write_Command(SSD1351_CMD_SETROW);
  Write_Data(y);
  Write_Data(y+h-1);
  // fill!
  Write_Command(SSD1351_CMD_WRITERAM);  
  
  for (uint16_t i=0; i < w*h; i++) {
    Write_Data(color_fill_byte[0]);
    Write_Data(color_fill_byte[1]);
  }
}


void Fill_Circle(int16_t x0, int16_t y0, int16_t r) {
  
  Draw_FastVLine(x0, y0-r, 2*r+1);
  FillCircle_Helper(x0, y0, r, 3, 0);
}


// Used to do circles and roundrects
void FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta)  {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while(x<y)  {
    if(f >= 0)  {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if(corner & 0x1)  {
      Draw_FastVLine(x0+x, y0-y, 2*y+1+delta);
      Draw_FastVLine(x0+y, y0-x, 2*x+1+delta);
    }
    if(corner & 0x2)  {
      Draw_FastVLine(x0-x, y0-y, 2*y+1+delta);
      Draw_FastVLine(x0-y, y0-x, 2*x+1+delta);
    }
  }
}


// Draw a circle outline
void Draw_Circle(int16_t x0, int16_t y0, int16_t r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  Draw_Pixel(x0  , y0+r);
  Draw_Pixel(x0  , y0-r);
  Draw_Pixel(x0+r, y0  );
  Draw_Pixel(x0-r, y0  );

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    Draw_Pixel(x0 + x, y0 + y);
    Draw_Pixel(x0 - x, y0 + y);
    Draw_Pixel(x0 + x, y0 - y);
    Draw_Pixel(x0 - x, y0 - y);
    Draw_Pixel(x0 + y, y0 + x);
    Draw_Pixel(x0 - y, y0 + x);
    Draw_Pixel(x0 + y, y0 - x);
    Draw_Pixel(x0 - y, y0 - x);
    }
}


// Draw a rounded rectangle
void Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r) {
    // smarter version
    Draw_FastHLine(x+r  , y    , w-2*r); // Top
    Draw_FastHLine(x+r  , y+h-1, w-2*r); // Bottom
    Draw_FastVLine(x    , y+r  , h-2*r); // Left
    Draw_FastVLine(x+w-1, y+r  , h-2*r); // Right
    // draw four corners
    DrawCircle_Helper(x+r    , y+r    , r, 1);
    DrawCircle_Helper(x+w-r-1, y+r    , r, 2);
    DrawCircle_Helper(x+w-r-1, y+h-r-1, r, 4);
    DrawCircle_Helper(x+r    , y+h-r-1, r, 8);
}


void DrawCircle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t corner) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (corner & 0x4) {
      Draw_Pixel(x0 + x, y0 + y);
      Draw_Pixel(x0 + y, y0 + x);
    }
    if (corner & 0x2) {
      Draw_Pixel(x0 + x, y0 - y);
      Draw_Pixel(x0 + y, y0 - x);
    }
    if (corner & 0x8) {
      Draw_Pixel(x0 - y, y0 + x);
      Draw_Pixel(x0 - x, y0 + y);
    }
    if (corner & 0x1) {
      Draw_Pixel(x0 - y, y0 - x);
      Draw_Pixel(x0 - x, y0 - y);
    }
  }
}


// Draw a triangle
void Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)  {
  Draw_Line(x0, y0, x1, y1);
  Draw_Line(x1, y1, x2, y2);
  Draw_Line(x2, y2, x0, y0);
}

void Display_Interface(void) {
  
  uint16_t i,color;
  RAM_Address();
  Write_Command(0x5C);
  for(i = 0 ; i < 128*63 ; i++)  {
    if((interface_1[i/8]>>(i%8))&0x01) {
      
      if(i<128*12)
        color = GREEN+(i<<11);
      else if(i<128*40)
        color = CYAN;
      else
        color = RED+i-128*40;
    }
    else  {
      color = BLACK;
    }
    Set_Color(color);
    Write_Data(color_byte[0]);
    Write_Data(color_byte[1]);
  }

  for(i = 0 ; i < 128*64*2 ; i+=2)  {
    if(interface_2[i] != 0x00)
      color_byte[0] = interface_2[i];
    else
      color_byte[0] = interface_2[i];
    if(interface_2[i] != 0x00)
      color_byte[1] = 0xe0;
    else
      color_byte[1] = interface_2[i+1];
    Write_Data(color_byte[0]);
    Write_Data(color_byte[1]);
  }
}


void Display_bmp(void) {
  uint16_t i = 0;
  RAM_Address();
  Write_Command(0x5C);
  
  for( ; i < 128*128*2; i+=2)  {
    color_byte[0] = gImage_bmp2[i];
    color_byte[1] = gImage_bmp2[i+1];
    Write_Data(color_byte[0]);
    Write_Data(color_byte[1]);
  }
}



