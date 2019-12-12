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
    int i =0;
    while (1)
    {
        
        
        
        if ( digitalRead(36)==0)
        {
            if(i==3)
            {
                i=0;
            }
            else
            i++;
            
        }

        //*****write 'START' on the display****************
        if(i==0)
        { 
            ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,0,31,0);
            ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
            ssd1331OLED->setFont(Lato_Regular_20);
            ssd1331OLED->drawString(50,30,"START",BLUE);
            delay(4000);

            ssd1331OLED->Display_Clear(0, 0, 95, 63);
        }
       
        //******write 'PAUSE' on the display**************
         if(i==1)
         {
            ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,0,31,0);
            ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
            ssd1331OLED->setFont(Lato_Regular_20);
            ssd1331OLED->drawString(50,30,"PAUSE",BLUE);
            delay(4000);
        
            ssd1331OLED->Display_Clear(0, 0, 95, 63);
        }

        //****** write 'RUN' on the display*********
        if(i==2)
        {
            ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,0,31,0);
            ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
            ssd1331OLED->setFont(Lato_Regular_20);
            ssd1331OLED->drawString(50,30,"RUN",BLUE);
            delay(4000);

            ssd1331OLED->Display_Clear(0, 0, 95, 63);
        }

        //*****write 'FAILURE' on the display****************
        if(i==3)
        {
            ssd1331OLED->Drawing_Rectangle_Line(0,15,95,46,31,0,0);
            ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
            ssd1331OLED->setFont(Lato_Regular_20);
            ssd1331OLED->drawString(50,30,"FAILURE",BLUE);
            delay(4000);

            ssd1331OLED->Display_Clear(0, 0, 95, 63);
        }
    }
} 