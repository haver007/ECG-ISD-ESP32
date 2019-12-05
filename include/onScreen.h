#define COLOR_SCREEN

#include "ESP32_SSD1331.h"
#include "SSD1331Extended.h"
#include "fonts.h"

class onScreen
{
private:
    const uint8_t SCLK_OLED = 14; //SCLK
    const uint8_t MOSI_OLED = 13; //MOSI (Master Output Slave Input)
    const uint8_t MISO_OLED = 12; // (Master Input Slave Output)
    const uint8_t CS_OLED = 15;
    const uint8_t DC_OLED = 16; //OLED DC(Data/Command)
    const uint8_t RST_OLED = 4; //OLED Reset
    SSD1331Extended* ssd1331OLED;
 
    
public:
    onScreen(/* args */);
    ~onScreen();
    void loop();
};
