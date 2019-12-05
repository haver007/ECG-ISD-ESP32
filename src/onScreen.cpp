#include "onScreen.h"

onScreen::onScreen(/* args */)
{
    ssd1331OLED = new SSD1331Extended(SCLK_OLED, MISO_OLED, MOSI_OLED, CS_OLED, DC_OLED, RST_OLED);
    ssd1331OLED->SSD1331_Init();
    pinMode(36, INPUT);

}

onScreen::~onScreen()
{
    if (ssd1331OLED != NULL)
    {
        delete ssd1331OLED;
        ssd1331OLED = NULL;
    }
}
void onScreen::loop()
{
    
    while (1)
    {
        //int i, j;
        //uint8_t R, G, B, Dot1, Dot2;
        static uint8_t _colon_fnt_S[2][16] = {
        0b00011110,
        0b01110000,
        0b11100000,
        0b11000000,
        0b11000000,
        0b11100000,
        0b00111000,
        0b00011100,
        0b00000111,
        0b00000011,
        0b00000011,
        0b00000111,
        0b00001110,
        0b00011100,
        0b01110000,
        0b11100000,
        };

        static uint8_t _colon_fnt_T[2][16] = {
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b11111111,
        0b11111111
        };

        static uint8_t _colon_fnt_A[2][16] = {
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11111111,
        0b11111111,
        0b11000011,
        0b11000011,
        0b11000011,
        0b01100110,
        0b01100110,
        0b00011000,
        0b00011000
        };
           static uint8_t _colon_fnt_R[2][16] = {
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11111111,
        0b11111111,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11111111,
        0b11111111
        };

        static uint8_t _colon_fnt_P[2][16] = {
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b11111111,
        0b11111111,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11111111,
        0b11111111
        };

        static uint8_t _colon_fnt_U[2][16] = {
        0b11111111,
        0b11111111,
        0b11000011,
        0b11000011,
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011, 
        0b11000011
        };
        static uint8_t _colon_fnt_E[2][16] = {
        0b11111111,
        0b11111111,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b11111111,
        0b11111111,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b11111111,
        0b11111111
        };
        
        static uint8_t _colon_fnt_N[2][16] = {  
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11111111,
        0b11111111,
        };

        static uint8_t _colon_fnt_I[2][16] = { 
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        };

        static uint8_t _colon_fnt_L[2][16] = { 
        0b11111111,
        0b11111111,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011
        };

        static uint8_t _colon_fnt_F[2][16] = {
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b11111111,
        0b11111111,
        0b00000011,
        0b00000011,
        0b00000011,
        0b00000011,
        0b11111111,
        0b11111111
        };
      /*  ssd1331->Display_Clear(0, 0, 95, 63);

        ssd1331->CommandWrite(0xAE); //Set Display Off
        delay(1000);

        ssd1331->CommandWrite(0xA0);       //Remap & Color Depth setting　
        ssd1331->CommandWrite(0b00110010); //A[7:6] = 00; 256 color.

        R = 7;
        G = 0;
        B = 0; //256 color : R (0-7), G (0-7), B (0-3)
        Dot1 = (R << 5) | (G << 2) | B;
        for (j = 0; j < 64; j++)
        {
            for (i = 0; i < 96; i++)
            {
                ssd1331->DataWrite(Dot1);
            }
        }

        ssd1331->CommandWrite(0xAF); //Set Display On
        delay(110);                  //0xAF100ms
        ssd1331->Brightness_FadeIn(4);
        delay(1000);
        ssd1331->Brightness_FadeOut(4);
        delay(1000);
        ssd1331->CommandWrite(0xAE); //Set Display Off
        delay(1000);

        ssd1331->Brightness_FadeIn(0);
        ssd1331->Display_Clear(0, 0, 95, 63);
        ssd1331->CommandWrite(0xAF); //Set Display On
        delay(110);                  //0xAF100ms
        R = 0;
        G = 7;
        B = 0; //256 color : R (0-7), G (0-7), B (0-3)
        Dot1 = (R << 5) | (G << 2) | B;
        for (j = 0; j < 64; j++)
        {
            for (i = 0; i < 96; i++)
            {
                ssd1331->DataWrite(Dot1);
            }
        }
        delay(2000);

        R = 0;
        G = 0;
        B = 3; //256 color : R (0-7), G (0-7), B (0-3)
        Dot1 = (R << 5) | (G << 2) | B;
        for (j = 0; j < 64; j++)
        {
            for (i = 0; i < 96; i++)
            {
                ssd1331->DataWrite(Dot1);
            }
        }
        delay(2000);

        ssd1331->Display_Clear(0, 0, 95, 63);

        ssd1331->CommandWrite(0xA0);       //Remap & Color Depth setting　
        ssd1331->CommandWrite(0b01110010); //A[7:6] = 01; 65k color format

        R = 31;
        G = 63;
        B = 31; //65k color : R (0-31), G (0-63), B (0-31)
        uint8_t DotDot[2];
        DotDot[0] = (R << 3) | (G >> 3);
        DotDot[1] = (G << 5) | B;
        for (j = 0; j < 64; j++)
        {
            for (i = 0; i < 96; i++)
            {
                ssd1331->DataWriteBytes(DotDot, 2); //65k colorモードでは、２バイトデータを送る
            }
        }
        delay(2000);

        ssd1331->Display_Clear(0, 0, 95, 63);
        ssd1331->Drawing_Line(0, 0, 95, 63, 31, 0, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Drawing_Line(95, 0, 0, 63, 0, 31, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Drawing_Line(48, 0, 48, 63, 0, 0, 31); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        for (i = 0; i < 63; i = i + 5)
        {
            ssd1331->Drawing_Line(i, 63, 95, 63 - i, 0, i, 31);
        }
        delay(2000);

        ssd1331->Display_Clear(0, 0, 95, 63);

       */
        // *********Display 95X63***********
        //*****write 'START' on the display****************
        
        /*ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,0,31,0);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,65,23,0,0,31,_colon_fnt_S);//Red(0-31), Green(0-63), Blue(0-31)
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,55,23,0,0,31,_colon_fnt_T);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,45,23,0,0,31,_colon_fnt_A);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,35,23,0,0,31,_colon_fnt_R);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,25,23,0,0,31,_colon_fnt_T);*/
        
        ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
        ssd1331OLED->setFont(ArialMT_Plain_10);
        ssd1331OLED->drawString(20,30,"START",BLUE);
        delay(4000);
        ssd1331OLED->Display_Clear(0, 0, 95, 63);
        
        //******write 'PAUSE' on the display**************
        ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,0,31,0);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,65,23,0,0,31,_colon_fnt_P);//Red(0-31), Green(0-63), Blue(0-31)
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,55,23,0,0,31,_colon_fnt_A);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,45,23,0,0,31,_colon_fnt_U);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,35,23,0,0,31,_colon_fnt_S);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,25,23,0,0,31,_colon_fnt_E);
        delay(4000);

        
        ssd1331OLED->Display_Clear(0, 0, 95, 63);

        //****** write 'RUN' on the display*********
        ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,0,31,0);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,55,23,0,0,31,_colon_fnt_R);//Red(0-31), Green(0-63), Blue(0-31)
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,45,23,0,0,31,_colon_fnt_U);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,35,23,0,0,31,_colon_fnt_N);
        delay(4000);

        ssd1331OLED->Display_Clear(0, 0, 95, 63);

        //*****write 'FAILURE' on the display****************
        ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,31,0,0);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,75,23,31,0,0,_colon_fnt_F);//Red(0-31), Green(0-63), Blue(0-31)
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,65,23,31,0,0,_colon_fnt_A);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,55,23,31,0,0,_colon_fnt_I);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,45,23,31,0,0,_colon_fnt_L);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,35,23,31,0,0,_colon_fnt_U);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,25,23,31,0,0,_colon_fnt_R);
        ssd1331OLED->SSD1331_8x16_Font_DisplayOut(1,15,23,31,0,0,_colon_fnt_E);
        delay(4000);

         ssd1331OLED->Display_Clear(0, 0, 95, 63);
      /*  ssd1331->Drawing_Rectangle_Line(20, 20, 40, 40, 31, 0, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Drawing_Rectangle_Line(0, 0, 60, 60, 0, 31, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Drawing_Rectangle_Line(70, 10, 80, 63, 0, 0, 31); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Display_Clear(0, 0, 95, 63);
        ssd1331->Drawing_Rectangle_Fill(0, 0, 60, 60, 0, 31, 0, 31, 0, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Drawing_Rectangle_Fill(20, 20, 40, 40, 0, 0, 31, 0, 31, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Drawing_Rectangle_Fill(70, 10, 80, 63, 31, 63, 31, 0, 0, 31); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Display_Clear(0, 0, 95, 63);

        ssd1331->CommandWrite(0xA0);       //Remap & Color Depth setting　
        ssd1331->CommandWrite(0b00110010); //A[7:6] = 00; 256 color.

        ssd1331->Drawing_Circle_Line_256color(31, 31, 31, 7, 0, 0); //Red(0-7), Green(0-7), Blue(0-3)
        delay(2000);
        ssd1331->Drawing_Circle_Line_256color(50, 31, 20, 0, 7, 0); //Red(0-7), Green(0-7), Blue(0-3)
        delay(2000);
        ssd1331->Drawing_Circle_Line_256color(70, 31, 10, 0, 0, 3); //Red(0-7), Green(0-7), Blue(0-3)
        delay(2000);

        ssd1331->Display_Clear(0, 0, 95, 63);

        ssd1331->Drawing_Circle_Fill(31, 31, 31, 31, 0, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);
        ssd1331->Drawing_Circle_Fill(50, 31, 20, 0, 63, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);
        ssd1331->Drawing_Circle_Fill(70, 31, 10, 0, 0, 31); //Red(0-31), Green(0-63), Blue(0-31)
        delay(2000);

        ssd1331->Display_Clear(0, 0, 95, 63);
        ssd1331->CommandWrite(0xA0);       //Remap & Color Depth setting　
        ssd1331->CommandWrite(0b01110010); //A[7:6] = 01; 65k color format

        ssd1331->Drawing_Circle_Line_65kColor(31, 31, 31, 0, 63, 31); //Red(0-31), Green(0-63), Blue(0-31)
        delay(1000);
        ssd1331->Drawing_Circle_Line_65kColor(50, 31, 20, 31, 0, 31); //Red(0-31), Green(0-63), Blue(0-31)
        delay(1000);
        ssd1331->Drawing_Circle_Line_65kColor(70, 31, 10, 31, 31, 0); //Red(0-31), Green(0-63), Blue(0-31)
        delay(1000);

        ssd1331->SSD1331_Copy(60, 21, 80, 41, 0, 0);
        ssd1331->SSD1331_Copy(60, 21, 80, 41, 75, 0);
        ssd1331->SSD1331_Copy(60, 21, 80, 41, 0, 43);

        for (i = 0; i < 76; i++)
        {
            ssd1331->SSD1331_Copy(60, 21, 80, 41, 75 - i, 43);
            if (i > 0)
            {
                ssd1331->Display_Clear(96 - i, 43, 95, 63);
            }
            delay(20);
        }
        delay(2000);
        */
    }
} 