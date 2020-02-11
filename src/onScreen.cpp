#include "onScreen.h"
const std::map<onScreen::State, std::string> onScreen::StateDescription = {

 {State::Failure,"Failure"},
 {State::Menue_1_active,"Menue_1_active"},
 {State::UnterMenue_1_active,"UnterMenue_1_active"},
 {State::UnterMenue_2_active,"UnterMenue_2_active"},
 {State::NOT_Measurement,"NOT_Measurement"},
 {State::NOT_Measurement,"NOT_Stop"},
 {State::Menue_2_active,"Menue_2_active"},
 {State::Menue_3_active,"Menue_3_active"},
 {State::Measurement_active,"Measurement_active"},
 {State::Measurement_stop,"Measurement_stop"},
 {State::WLAN_toggle,"WLAN_toggle"},
 {State::WLAN_active,"WLAN_active"},
 {State::NOT_WLAN_ON,"NOT_WLAN_ON"},
 {State::WLAN_toggle,"WLAN_toggle_OFF"},
 {State::WLAN_toggle,"WLAN_OFF"},
 {State::WLAN_toggle,"NOT_WLAN_OFF"},
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
    pinMode(34, INPUT_PULLDOWN);
    pinMode(33, INPUT_PULLDOWN);
    pinMode(32, INPUT_PULLDOWN);
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
    state(State::Menue_1_active);
    ssd1331OLED->Drawing_Rectangle_Line(0,0,60,20,31,0,0);
            
}
void onScreen::onEntering_UnterMenue_1_active(){
     state(State::UnterMenue_1_active);
     ssd1331OLED->Display_Clear_all();
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3,"Start Measurement?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,31,0,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,0,31,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);
            

}
void onScreen::onEntering_UnterMenue_2_active(){
    state(State::UnterMenue_2_active);
     ssd1331OLED->Display_Clear_all();
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3," Stop Measurement?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,31,0,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,0,31,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);
}
void onScreen::onEntering_NOT_Measurement(){
     state(State::NOT_Measurement);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3,"Start Measurement?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,0,31,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,31,0,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);

}
void onScreen::onEntering_NOT_Stop(){
     state(State::NOT_Stop);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3,"Stop Measurement?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,0,31,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,31,0,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);
}
void onScreen::onEntering_Menue_2_active(){
    state(State::Menue_2_active);
    ssd1331OLED->Drawing_Rectangle_Line(0,22,60,41,31,0,0);

}
void onScreen::onEntering_Menue_3_active(){
    state(State::Menue_3_active);
    ssd1331OLED->Drawing_Rectangle_Line(0,43,60,62,31,0,0);
}
void onScreen::onEntering_Measurement_active(){
    state(State::Measurement_active);
    ssd1331OLED->Drawing_Rectangle_Line(4,22,85,41,0,31,0);
    ssd1331OLED->drawString(80,21,"RUNNING",BLUE); 
}
void onScreen::onEntering_Measurement_stop(){
    state(State::Measurement_stop);
    ssd1331OLED->Drawing_Rectangle_Line(18,22,67,41,0,31,0);
    ssd1331OLED->drawString(57,21,"stop",BLUE); 
}
void onScreen::onEntering_Info_SD(){

}
void onScreen::onEntering_WLAN_toggle(){
    state(State::WLAN_toggle);
     ssd1331OLED->Display_Clear_all();
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3," Start WLAN?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,31,0,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,0,31,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);

}
void onScreen::onEntering_WLAN_active(){
    state(State::Measurement_active);
    //ssd1331OLED->Drawing_Rectangle_Line(18,22,67,41,0,31,0);
    ssd1331OLED->Drawing_Rectangle_Line(5,22,90,41,0,31,0);
    //ssd1331OLED->drawString(57,21,"WLAN is on",BLUE);
    ssd1331OLED->drawString(90,21,"WLAN is on",BLUE);
}

void onScreen::onEntering_Not_WLAN_On(){
    state(State::NOT_WLAN_ON);
     ssd1331OLED->Display_Clear_all();
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3," Start WLAN?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,0,31,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,31,0,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);

}
void onScreen::onEntering_WLAN_toggle_OFF(){
     state(State::WLAN_toggle_OFF);
     ssd1331OLED->Display_Clear_all();
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3," Stop WLAN?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,31,0,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,0,31,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);
}
void onScreen::onEntering_NOT_WLAN_OFF(){
    state(State::NOT_WLAN_OFF);
     ssd1331OLED->Display_Clear_all();
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_CENTER); 
     ssd1331OLED->setFont(Lato_Hairline_10);
     ssd1331OLED->drawString(47,3," Stop WLAN?",BLUE);
     ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT);
     ssd1331OLED->setFont(Lato_Hairline_16);
     ssd1331OLED->Drawing_Rectangle_Line(25,22,67,41,0,31,0);
     ssd1331OLED->drawString(57,21,"YES",BLUE);     
     ssd1331OLED->Drawing_Rectangle_Line(25,43,67,62,31,0,0);
     ssd1331OLED->drawString(57,43,"NO",BLUE);

}
void onScreen::onEntering_WLAN_OFF(){
    state(State::WLAN_OFF);
    ssd1331OLED->Drawing_Rectangle_Line(5,22,92,41,0,31,0);
    ssd1331OLED->drawString(90,21,"WLAN OFF",BLUE); 

}
void onScreen::onEntering_Idle(){
    state(State::Idle);
    
}
void onScreen::onEntering_Failure(){

}
void onScreen::onLeaving_Menue_1_active(){
    ssd1331OLED->Drawing_Rectangle_Line(0,0,60,20,0,31,0);
}
void onScreen::onLeaving_UnterMenue_1_active(){
    ssd1331OLED->Display_Clear_all();
}
void onScreen::onLeaving_UnterMenue_2_active(){
}
void onScreen::onLeaving_Menue_2_active(){
    ssd1331OLED->Drawing_Rectangle_Line(0,22,60,41,0,31,0);
}
void onScreen::onLeaving_Menue_3_active(){
    ssd1331OLED->Drawing_Rectangle_Line(0,43,60,62,0,31,0);
}
void onScreen::onLeaving_Measurement_active(){
    ssd1331OLED->Display_Clear_all();
    onLeaving_Idle();
}
void onScreen::onLeaving_Measurement_stop(){
    onLeaving_Idle();
}
void onScreen::onLeaving_NOT_Measurement(){

}
void onScreen::onLeaving_NOT_Stop(){

}
void onScreen::onLeaving_Info_SD(){


}
void onScreen::onLeaving_WLAN_toggle(){
    ssd1331OLED->Display_Clear_all();
}
void onScreen::onLeaving_Not_WLAN_On(){

}
void onScreen::onLeaving_WLAN_active(){
    ssd1331OLED->Display_Clear_all();
    onLeaving_Idle();
}
void onScreen::onLeaving_WLAN_toggle_OFF(){
    ssd1331OLED->Display_Clear_all();
}
void onScreen::onLeaving_WLAN_OFF(){
    ssd1331OLED->Display_Clear_all();
    onLeaving_Idle();

}
void onScreen::onLeaving_NOT_WLAN_OFF(){

}
void onScreen::onLeaving_Idle(){
            //Setup Menue when changing from idle to active
            ssd1331OLED->Display_Clear_all();
            ssd1331OLED->Drawing_Rectangle_Line(0,22,60,41,0,31,0);
            ssd1331OLED->Drawing_Rectangle_Line(0,43,60,62,0,31,0);
            ssd1331OLED->setTextAlignment(TEXT_ALIGN_RIGHT); 
            ssd1331OLED->setFont(Lato_Hairline_16);
            //Blue = yellow :D
            ssd1331OLED->drawString(50,1,"START",BLUE);
            ssd1331OLED->drawString(50,21,"WLAN",BLUE);
            ssd1331OLED->drawString(50,41,"INFO",BLUE);
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
	
	/* --Start with initial transition Idle (display off). */
	onEntering_Idle();
	
}
void onScreen::restart() {
	/* --Same as start. */
	start();
}
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
    /* --State machine as nested switch case for menue. */
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
        case Event::right_pressed:onLeaving_Menue_1_active();onEntering_UnterMenue_1_active(); break;
		case Event::left_pressed:onLeaving_Menue_1_active();onEntering_UnterMenue_2_active(); break;
        case Event::down_pressed:onLeaving_Menue_1_active();onEntering_Menue_2_active(); break;
        case Event::up_pressed:onLeaving_Menue_1_active();onEntering_Menue_3_active(); break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::UnterMenue_1_active:
		switch (ev) {
        case Event::right_pressed:onLeaving_UnterMenue_1_active(),onEntering_Measurement_active();break;
		case Event::left_pressed: break;
        case Event::down_pressed:onLeaving_UnterMenue_1_active(),onEntering_NOT_Measurement(); break;
        case Event::up_pressed: onLeaving_UnterMenue_1_active(),onEntering_NOT_Measurement();break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::UnterMenue_2_active:
		switch (ev) {
        case Event::right_pressed:break;
		case Event::left_pressed:onLeaving_UnterMenue_1_active(),onEntering_Measurement_stop(); break;
        case Event::down_pressed:onLeaving_UnterMenue_1_active(),onEntering_NOT_Stop(); break;
        case Event::up_pressed:onLeaving_UnterMenue_1_active(),onEntering_NOT_Stop(); break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
     case State::NOT_Measurement:
		switch (ev) {
        case Event::right_pressed:break;
		case Event::left_pressed:onLeaving_NOT_Measurement(),onLeaving_Idle(),onEntering_Menue_1_active();break;
        case Event::down_pressed:onLeaving_NOT_Measurement(),onEntering_UnterMenue_1_active(); break;
        case Event::up_pressed:onLeaving_NOT_Measurement(),onEntering_UnterMenue_1_active(); break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::NOT_Stop:
		switch (ev) {
        case Event::right_pressed:onLeaving_NOT_Stop(),onLeaving_Idle(),onEntering_Menue_1_active();break;
		case Event::left_pressed: break;
        case Event::down_pressed:onLeaving_NOT_Stop(),onEntering_UnterMenue_2_active(); break;
        case Event::up_pressed:onLeaving_NOT_Stop(),onEntering_UnterMenue_2_active(); break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::Measurement_active:
        switch (ev) {
		case Event::right_pressed:onLeaving_Measurement_active(); onEntering_Menue_1_active();break;
		case Event::left_pressed: break;
        case Event::down_pressed: break;
        case Event::up_pressed:   break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::Measurement_stop:
        switch (ev) {
		case Event::right_pressed:break;
		case Event::left_pressed: onLeaving_Measurement_stop(),onEntering_Menue_1_active();break;
        case Event::down_pressed: break;
        case Event::up_pressed:   break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
	case State::Menue_2_active:
		switch (ev) {
		case Event::right_pressed:onLeaving_Menue_2_active();onEntering_WLAN_toggle();break;
		case Event::left_pressed: onLeaving_Menue_2_active();onEntering_WLAN_toggle_OFF();break;
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
		case Event::right_pressed: onLeaving_WLAN_toggle(),onEntering_WLAN_active();break;
		case Event::left_pressed: break;
        case Event::down_pressed: onLeaving_WLAN_toggle(), onEntering_Not_WLAN_On(); break;
        case Event::up_pressed: onLeaving_WLAN_toggle(), onEntering_Not_WLAN_On();break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::WLAN_active:
		switch (ev) {
		case Event::right_pressed: onLeaving_WLAN_active(),onEntering_Menue_1_active();break;
		case Event::left_pressed: break;
        case Event::down_pressed: break;
        case Event::up_pressed: break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
     case State::NOT_WLAN_ON:
		switch (ev) {
		case Event::right_pressed:break;
		case Event::left_pressed:onLeaving_Not_WLAN_On(),onLeaving_Idle(),onEntering_Menue_1_active(); break;
        case Event::down_pressed:onLeaving_Not_WLAN_On(),onEntering_WLAN_toggle();break;
        case Event::up_pressed: onLeaving_Not_WLAN_On(),onEntering_WLAN_toggle();break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break; 
    case State::WLAN_toggle_OFF:
		switch (ev) {
		case Event::right_pressed:break;
		case Event::left_pressed: onLeaving_WLAN_toggle_OFF(),onEntering_WLAN_OFF();break;
        case Event::down_pressed: onLeaving_WLAN_toggle_OFF(), onEntering_NOT_WLAN_OFF(); break;
        case Event::up_pressed: onLeaving_WLAN_toggle_OFF(), onEntering_NOT_WLAN_OFF();break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::NOT_WLAN_OFF:
		switch (ev) {
		case Event::right_pressed:onLeaving_NOT_WLAN_OFF(),onLeaving_Idle(),onEntering_Menue_1_active();break;
		case Event::left_pressed:break;
        case Event::down_pressed:onLeaving_NOT_WLAN_OFF(),onEntering_WLAN_toggle_OFF();break;
        case Event::up_pressed: onLeaving_NOT_WLAN_OFF(),onEntering_WLAN_toggle_OFF();break;
        case Event::none: break;
		default: onEntering_Failure();
		}
		break;
    case State::WLAN_OFF:
		switch (ev) {
		case Event::right_pressed: break;
		case Event::left_pressed: onLeaving_WLAN_OFF(),onEntering_Menue_1_active();break;
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

//Method for checking Input changes
void onScreen::loop()
{   
    while (1)
    {
        Event ev= Event::none;
        if(digitalRead(36)==0){
            ev= Event::right_pressed;
            delay(500);
        }
        
        if(digitalRead(34)==1){
            ev= Event::left_pressed;
            delay(400);
        }
        if(digitalRead(32)==1){
            ev= Event::down_pressed;
            delay(400);
        }
        if(digitalRead(33)==1){
            ev= Event::up_pressed;
            delay(400);
        }
        
        if (ev != Event::none)
        handle(ev);
    }
} 