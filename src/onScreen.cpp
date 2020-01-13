#include "onScreen.h"
const std::map<onScreen::State, std::string> onScreen::StateDescription = {

 {State::Failure,"Failure"},
 {State::Menue_1_active,"Menue_1_active"},
 {State::Menue_2_active,"Menue_2_active"},
 {State::Menue_3_active,"Menue_3_active"},
 {State::Measurement_active,"Measurement_active"},
 {State::WLAN_toggle,"WLAN_toggle"},
 {State::Info_SD,"Info_SD"},
 {State::Idle,"Idle"} 

};
const std::map<onScreen::Event, std::string> onScreen::EventDescription = {
	{ Event::right_pressed, "right_pressed"}, 
    { Event::left_pressed, "left_pressed"},
    { Event::down_pressed, "down_pressed"},
    { Event::up_pressed, "up_pressed"},
    { Event::none, "none"},   
};
onScreen::onScreen(/* args */)
{
    ssd1331OLED = new SSD1331Extended(SCLK_OLED, MISO_OLED, MOSI_OLED, CS_OLED, DC_OLED, RST_OLED);
    ssd1331OLED->SSD1331_Init();
    pinMode(36, INPUT);
    pinMode(34, INPUT);
    pinMode(33, INPUT);
    pinMode(32, INPUT);
    //initialize state of Menu (IDLE)
    start();

}
onScreen::~onScreen()
{
    if (ssd1331OLED != NULL)
    {
        delete ssd1331OLED;
        ssd1331OLED = NULL;
    }
}
void onScreen::onEntering_Menue_1_active(){
        //
            ssd1331OLED->Drawing_Rectangle_Line(0,0,60,20,31,0,0);
            ssd1331OLED->Drawing_Rectangle_Line(0,22,60,41,0,31,0);
            ssd1331OLED->Drawing_Rectangle_Line(0,43,60,62,0,31,0);
            ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT); 
            ssd1331OLED->setFont(Lato_Hairline_16);
            //Blue = yellow :D
            ssd1331OLED->drawString(50,1,"START",BLUE);
            ssd1331OLED->drawString(50,21,"WLAN",BLUE);
            ssd1331OLED->drawString(50,41,"INFO",BLUE);
            state(State::Menue_1_active);
}
void onScreen::onEntering_Menue_2_active(){
    state(State::Menue_2_active);
    ssd1331OLED->Drawing_Rectangle_Line(0,0,60,20,0,31,0);
    ssd1331OLED->Drawing_Rectangle_Line(0,22,60,41,31,0,0);
    
}
void onScreen::onEntering_Menue_3_active(){
    state(State::Menue_3_active);
    ssd1331OLED->Drawing_Rectangle_Line(0,22,60,41,0,31,0);
    ssd1331OLED->Drawing_Rectangle_Line(0,43,60,62,31,0,0);
}
void onScreen::onEntering_Measurement_active(){

}
void onScreen::onEntering_Info_SD(){

}
void onScreen::onEntering_WLAN_toggle(){

}
void onScreen::onEntering_Idle(){
    state(State::Idle);
    
}
void onScreen::onEntering_Failure(){

}
void onScreen::onLeaving_Menue_1_active(){

}
void onScreen::onLeaving_Menue_2_active(){

}
void onScreen::onLeaving_Menue_3_active(){

}
void onScreen::onLeaving_Measurement_active(){

}
void onScreen::onLeaving_Info_SD(){


}
void onScreen::onLeaving_WLAN_toggle(){

}
void onScreen::onLeaving_Idle(){

}
void onScreen::onLeaving_Failure(){

}
void onScreen:: state (State s){
/* --Log state chance. Check if description is available. */
	bool isOldStateAvailable = (StateDescription.find(mystate) != StateDescription.end());
	bool isNewStateAvailable = (StateDescription.find(s) != StateDescription.end());
	/* --Log string. */
	std::string note = std::string("OLD STATE:") + (isOldStateAvailable ? StateDescription.at(mystate) : "*ERROR*")
		+ std::string(" --> NEW STATE:") + (isNewStateAvailable ? StateDescription.at(s) : "*ERROR*");
	/* --Set new state.*/
	mystate = s;
}
/* --INFO: Do not touch this method. */
onScreen::State onScreen::state() const { return mystate; }
void onScreen::start() {
	
	/* --Start with initial transition. */
	onEntering_Idle();
	
}
void onScreen::restart() {
	/* --Same as start. */
	start();
}
/* --INFO: Do not touch this method. */
void onScreen::handle(Event ev) {
	State old = mystate;

	/* --Logging information. */
	//bool isEventAvailable = (EventDescription.find(ev) != EventDescription.end());
	/* --If program stops here, you have to add an event description to the map at top of this file !!! */
    /* --Process the event. */
	transition(ev);
    if (old == mystate){
        Serial.println("MAYBE UNHANDLED TRIGGER");
    }

}
void onScreen::transition(Event ev){
    /* --State machine as nested switch case. */
	switch (mystate) {
	case State::Idle:
		switch (ev) {
		case Event::right_pressed: onLeaving_Idle(); onEntering_Menue_1_active(); break;
		case Event::left_pressed: break;
        case Event::down_pressed: break;
        case Event::up_pressed: break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
	case State::Menue_1_active:
		switch (ev) {
        case Event::right_pressed:onLeaving_Menue_1_active();onEntering_Measurement_active(); break;
		case Event::left_pressed: break;
        case Event::down_pressed:onLeaving_Menue_1_active();onEntering_Menue_2_active(); break;
        case Event::up_pressed:onLeaving_Menue_1_active();onEntering_Menue_3_active(); break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
	case State::Menue_2_active:
		switch (ev) {
		case Event::right_pressed:onLeaving_Menue_2_active();onEntering_WLAN_toggle();break;
		case Event::left_pressed: break;
        case Event::down_pressed: onLeaving_Menue_2_active();onEntering_Menue_3_active();break;
        case Event::up_pressed: onLeaving_Menue_2_active();onEntering_Menue_1_active();break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
	case State::Menue_3_active:
		switch (ev) {
		case Event::right_pressed:onLeaving_Menue_3_active();onEntering_Info_SD(); break;
		case Event::left_pressed: break;
        case Event::down_pressed:onLeaving_Menue_3_active();onEntering_Menue_1_active(); break;
        case Event::up_pressed: onLeaving_Menue_3_active();onEntering_Menue_2_active();break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
	case State::WLAN_toggle:
		switch (ev) {
		case Event::right_pressed:break;
		case Event::left_pressed:onLeaving_WLAN_toggle();onEntering_Menue_2_active(); break;
        case Event::down_pressed: break;
        case Event::up_pressed: break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::Info_SD:
		switch (ev) {
		case Event::right_pressed:break;
		case Event::left_pressed:onLeaving_Info_SD();onEntering_Menue_3_active(); break;
        case Event::down_pressed: break;
        case Event::up_pressed: break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
	default: state(State::Failure);
	};
}

void onScreen::loop()
{   
    while (1)
    {
        Event ev= Event::none;
        if(digitalRead(36)==0){
            ev= Event::right_pressed;
        }
        
        if(digitalRead(34)==1){
            ev= Event::left_pressed;
        }
        if(digitalRead(32)==1){
            ev= Event::down_pressed;
        }
        if(digitalRead(33)==1){
            ev= Event::up_pressed;
        }
        
        if (ev != Event::none)
        handle(ev);
    }
} 