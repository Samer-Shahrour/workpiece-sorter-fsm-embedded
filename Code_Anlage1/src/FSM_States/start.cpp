#include <iostream>
#include "../../header/Hal/Actuators.h"
#include "../../header/FSM_States/start.h"
#include "../../header/FSM_States/stop.h"
#include "../../header/FSM_States/not1.h"
#include "../../header/FSM_States/not2.h"
using namespace std;

void Start::showState() {
    cout << "current State: start" << endl;
}

void Start::m1_start_pressed(){
	data->actuators.moveConveyorBelt(MOVE_RIGHT);
	new(this) Stop;
}

void Start::m1_estop_pressed(){
    data->actuators.lampSwitchOn(RED);
    data->actuators.stopConveyorBelt();
    new(this) Not1;
}

void Start::m2_estop_pressed(){
    data->actuators.lampSwitchOn(RED);
    data->actuators.stopConveyorBelt();
    new(this) Not2;
}


