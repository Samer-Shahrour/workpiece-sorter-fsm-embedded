#include "../../header/FSM_States/start.h"
#include "../../header/FSM_States/stop.h"
#include "../../header/FSM_States/not.h"
#include "../../header/FSM_States/not1.h"
#include "../../header/FSM_States/not2.h"
#include "../../header/FSM_States/reset.h"
using namespace std;


void Not1::showState() {
    cout << "current State: Not1" << endl;
}



void Not1::m1_estop_released() {
    data->actuators.lampSwitchOff(RED);
    data->actuators.lampSwitchOn(YELLOW);
    new(this) Reset;
}


void Not1::m2_estop_pressed(){
    new(this) Not;
}


