#include "../../header/FSM_States/start.h"
#include "../../header/FSM_States/stop.h"
#include "../../header/FSM_States/not1.h"
#include "../../header/FSM_States/not2.h"
#include "../../header/FSM_States/reset.h"
using namespace std;


void Reset::showState() {
    cout << "current State: Reset" << endl;
}

void Reset::m1_estop_pressed() {
    data->actuators.lampSwitchOff(YELLOW);
    data->actuators.lampSwitchOn(RED);
    new(this) Not1;
}

void Reset::m1_reset_pressed(){
    data->actuators.lampSwitchOff(YELLOW);
    new (this) Start;
}

void Reset::m2_estop_pressed(){
    data->actuators.lampSwitchOff(YELLOW);
    data->actuators.lampSwitchOn(RED);
    new(this) Not2;
}