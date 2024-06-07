#include <iostream>

#include "../../header/FSM_States/stop.h"
#include "../../header/FSM_States/start.h"
#include "../../header/FSM_States/not1.h"
#include "../../header/FSM_States/not2.h"
using namespace std;


void Stop::showState() {
    cout << "current State: Stop" << endl;
}

void Stop::m1_stop_pressed(){
	data->actuators.stopConveyorBelt();
	new(this) Start;
}


void Stop::m1_estop_pressed(){
    data->actuators.lampSwitchOn(RED);
    data->actuators.stopConveyorBelt();
    new(this) Not1;
}

void Stop::m2_estop_pressed(){
    data->actuators.lampSwitchOn(RED);
    data->actuators.stopConveyorBelt();
    new(this) Not2;
}

