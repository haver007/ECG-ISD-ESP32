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
void onEntering_Menue_1_active(){

};
void onEntering_Menue_2_active(){

};
void onEntering_Menue_3_active(){

};

void onLeaving_Menue_1_active(){

};
void onLeaving_Menue_2_active(){

};
void onLeaving_Menue_3_active(){
    
};

void onScreen::loop()
{
    while (1)
    {
        
        
        
        
    }
} 