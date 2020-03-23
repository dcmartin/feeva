#include "OLED_Driver.h"
#include "OLED_GFX.h"
#include <stdio.h>
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

void testlines(void);
void lcdTestPattern(void);
void testfastlines(void);
void testdrawrects(void);
void testfillrects(uint16_t color1, uint16_t color2);
void testfillcircles(uint8_t radius, uint16_t color);
void testdrawcircles(uint16_t color);
void testroundrects(void);
void testtriangles(void);


void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_ModuleExit();

    exit(0);
}

int main(int argc, char **argv)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    DEV_ModuleInit();
    Device_Init();
    DEV_Delay_ms(20);

    Display_Interface();
    DEV_Delay_ms(3000);
    Clear_Screen();
/*

    Set_Color(RED);
    print_String(0, 0, "Hello World !", FONT_5X8);
    Set_Color(BLUE);
    print_String(0, 8, "Hello waveshare", FONT_8X16);
    DEV_Delay_ms(2000);
    Clear_Screen();

    lcdTestPattern();
    DEV_Delay_ms(1000);

    testlines();
    DEV_Delay_ms(1000);

    testfastlines();
    DEV_Delay_ms(1000);

    testdrawrects();
    DEV_Delay_ms(1000);

    testfillrects(RED, YELLOW);
    DEV_Delay_ms(1000);

    Clear_Screen();
    testfillcircles(63, BLUE);
    DEV_Delay_ms(500);
    testdrawcircles(WHITE);
    DEV_Delay_ms(1000);

    testroundrects();
    DEV_Delay_ms(1000);

    testtriangles();
    DEV_Delay_ms(1000);
*/
    Display_bmp();

    DEV_Delay_ms(1000);
    return 0;
}

void testlines(void)
{

    Set_Color(RED);
    Clear_Screen();
    for (uint16_t x=0; x <= SSD1351_WIDTH - 1; x+=6)  {
        Draw_Line(0, 0, x, SSD1351_HEIGHT - 1);
        DEV_Delay_ms(20);
    }
    for (uint16_t y=0; y < SSD1351_HEIGHT - 1; y+=6)  {
        Draw_Line(0, 0, SSD1351_WIDTH - 1, y);
        DEV_Delay_ms(20);
    }

    Set_Color(YELLOW);
    Clear_Screen();
    for (uint16_t x=0; x < SSD1351_WIDTH - 1; x+=6) {
        Draw_Line(SSD1351_WIDTH - 1, 0, x, SSD1351_HEIGHT - 1);
        DEV_Delay_ms(20);
    }
    for (uint16_t y=0; y < SSD1351_HEIGHT - 1; y+=6) {
        Draw_Line(SSD1351_WIDTH - 1, 0, 0, y);
        DEV_Delay_ms(20);
    }

    Set_Color(BLUE);
    Clear_Screen();
    for (uint16_t x=0; x < SSD1351_WIDTH - 1; x+=6) {
        Draw_Line(0, SSD1351_HEIGHT - 1, x, 0);
        DEV_Delay_ms(20);
    }
    for (uint16_t y=0; y < SSD1351_HEIGHT - 1; y+=6) {
        Draw_Line(0, SSD1351_HEIGHT - 1, SSD1351_WIDTH - 1, y);
        DEV_Delay_ms(20);
    }

    Set_Color(GREEN);
    Clear_Screen();
    for (uint16_t x=0; x < SSD1351_WIDTH - 1; x+=6) {
        Draw_Line(SSD1351_WIDTH - 1, SSD1351_HEIGHT - 1, x, 0 );
        DEV_Delay_ms(20);
    }
    for (uint16_t y=0; y < SSD1351_HEIGHT - 1; y+=6) {
        Draw_Line(SSD1351_WIDTH - 1, SSD1351_HEIGHT - 1, 0, y);
        DEV_Delay_ms(20);
    }
}

void lcdTestPattern(void)
{
    uint32_t i,j;
    Set_Coordinate(0, 0);

    for(i=0; i<128; i++)  {
        for(j=0; j<128; j++)  {
            if(i<16)  {
                Set_Color(RED);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            } else if(i<32) {
                Set_Color(YELLOW);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            } else if(i<48) {
                Set_Color(GREEN);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            } else if(i<64) {
                Set_Color(CYAN);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            } else if(i<80) {
                Set_Color(BLUE);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            } else if(i<96) {
                Set_Color(MAGENTA);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            } else if(i<112)  {
                Set_Color(BLACK);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            } else {
                Set_Color(WHITE);
                Write_Data(color_byte[0]);
                Write_Data(color_byte[1]);
            }
        }
    }
}

void testfastlines(void)
{

    Set_Color(WHITE);
    Clear_Screen();

    for (uint16_t y=0; y < SSD1351_WIDTH - 1; y+=5) {
        Draw_FastHLine(0, y, SSD1351_WIDTH - 1);
        DEV_Delay_ms(10);
    }
    for (uint16_t x=0; x < SSD1351_HEIGHT - 1; x+=5) {
        Draw_FastVLine(x, 0, SSD1351_HEIGHT - 1);
        DEV_Delay_ms(10);
    }
}

void testdrawrects(void)
{
    Clear_Screen();
    for (uint16_t x=0; x < SSD1351_HEIGHT - 1; x+=6)  {
        Draw_Rect((SSD1351_WIDTH-1)/2 - x/2, (SSD1351_HEIGHT-1)/2 - x/2 , x, x);
        DEV_Delay_ms(10);
    }
}

void testfillrects(uint16_t color1, uint16_t color2)
{

    uint16_t x = SSD1351_HEIGHT;
    Clear_Screen();
    Set_Color(color1);
    Set_FillColor(color2);
    for(; x > 6; x-=6)  {
        Fill_Rect((SSD1351_WIDTH)/2 - x/2 + 1, (SSD1351_HEIGHT)/2 - x/2 + 1, x, x);
        Draw_Rect((SSD1351_WIDTH)/2 - x/2, (SSD1351_HEIGHT)/2 - x/2 , x, x);
    }
}

void testfillcircles(uint8_t radius, uint16_t color)
{

    Set_Color(color);

    Fill_Circle(64, 64, radius);
}


void testdrawcircles(uint16_t color)
{

    uint8_t r = 0;
    Set_Color(color);

    for (; r < SSD1351_WIDTH/2; r+=4)  {
        Draw_Circle(64, 64, r);
        DEV_Delay_ms(10);
    }
}

void testroundrects(void)
{
    int color = 100;
    int x = 0, y = 0;
    int w = SSD1351_WIDTH - 1, h = SSD1351_HEIGHT - 1;

    Clear_Screen();

    for(int i = 0 ; i <= 20; i++) {

        Draw_RoundRect(x, y, w, h, 5);
        x += 2;
        y += 3;
        w -= 4;
        h -= 6;
        color += 1100;
        Set_Color(color);
    }
}

void testtriangles(void)
{
    Clear_Screen();
    int color = 0xF800;
    int t;
    int w = SSD1351_WIDTH/2;
    int x = SSD1351_HEIGHT-1;
    int y = 0;
    int z = SSD1351_WIDTH;
    for(t = 0 ; t <= 15; t+=1) {
        Draw_Triangle(w, y, y, x, z, x);
        x-=4;
        y+=4;
        z-=4;
        color+=100;
        Set_Color(color);
    }
}



