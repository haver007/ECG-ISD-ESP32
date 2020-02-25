#define COLOR_SCREEN

#include "ESP32_SSD1331.h"
#include "SSD1331Extended.h"
#include "fonts.h"
#include <map>
#include <string>
using namespace std;

class onScreen
{
    public:
    onScreen(/* args */);
    ~onScreen();
    void loop();
    //Defining States and Events for the State Machine
    enum class State {Failure, Menue_1_active,UnterMenue_1_active,UnterMenue_2_active, Menue_2_active,
                     Menue_3_active,NOT_Measurement,NOT_Stop, Measurement_active,Measurement_stop,
                      WLAN_toggle,WLAN_active,NOT_WLAN_ON,WLAN_OFF, Info_SD, Idle};
    enum class Event {right_pressed,left_pressed, down_pressed, up_pressed,none,going_Idle};

    /* --Returns the current state. */
	State state() const;
	/* --Process the event using state transitions. */
	void handle(Event ev);

	/* --Start the state machine, set initial state. */
	void start();
	/* --Restart the state machine. */
	void restart();
	

private:
    const uint8_t SCLK_OLED = 14; //SCLK
    const uint8_t MOSI_OLED = 13; //MOSI (Master Output Slave Input)
    const uint8_t MISO_OLED = 12; // (Master Input Slave Output)
    const uint8_t CS_OLED = 15;
    const uint8_t DC_OLED = 16; //OLED DC(Data/Command)
    const uint8_t RST_OLED = 4; //OLED Reset
    bool WLAN_flag;
    uint16_t zaehler;
    SSD1331Extended* ssd1331OLED;
    State previousstate;
    State mystate;

	/* --Methods called when entering a state. */
	void onEntering_Menue_1_active();
    void onEntering_UnterMenue_1_active();
    void onEntering_UnterMenue_2_active();
    void onEntering_Menue_2_active();
    void onEntering_Menue_3_active();
    void onEntering_Measurement_active();
    void onEntering_Measurement_stop();
    void onEntering_NOT_Measurement();
    void onEntering_NOT_Stop();
    void onEntering_Info_SD();
    void onEntering_WLAN_toggle();
    void onEntering_WLAN_active();
    void onEntering_Not_WLAN_On();
    void onEntering_WLAN_OFF();
    void onEntering_Idle();
    void onEnteringMenue();
    void onEntering_Failure();

	/* --Methods called when leaving a state. */
	void onLeaving_Menue_1_active();
    void onLeaving_UnterMenue_1_active();
    void onLeaving_UnterMenue_2_active();
    void onLeaving_Menue_2_active();
    void onLeaving_Menue_3_active();
    void onLeaving_Measurement_active();
    void onLeaving_Measurement_stop();
    void onLeaving_NOT_Measurement();
    void onLeaving_NOT_Stop();
    void onLeaving_Info_SD();
    void onLeaving_WLAN_toggle();
    void onLeaving_WLAN_active();
    void onLeaving_Not_WLAN_On();
    void onLeaving_WLAN_OFF();
    void onLeaving_Idle();
    void onLeaving_Failure();

    /* --Sets the state explicitly. */
	void state(State s);
	/* --Process state transition; returns new state. */
	void transition(Event ev);

    /* --Constant names for debugging purpose. */
	static const std::map<State, std::string> StateDescription;
	static const std::map<Event, std::string> EventDescription;
};