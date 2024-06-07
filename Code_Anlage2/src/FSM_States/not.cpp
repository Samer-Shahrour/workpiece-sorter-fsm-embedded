#include "../../header/FSM_States/start.h"
#include "../../header/FSM_States/stop.h"
#include "../../header/FSM_States/not.h"
#include "../../header/FSM_States/not1.h"
#include "../../header/FSM_States/not2.h"
#include "../../header/FSM_States/reset.h"
using namespace std;


void Not::showState() {
    cout << "current State: Not" << endl;
}

void Not::m1_estop_released() {
    data->actuators.lampSwitchOff(RED);
    data->actuators.lampSwitchOn(YELLOW);
    new(this) Not2;
}

void Not::m2_estop_released(){
    data->actuators.lampSwitchOff(RED);
    data->actuators.lampSwitchOn(YELLOW);
    new(this) Not1;
}