#include <sys/neutrino.h>
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"
#include "../../../header/FSMs/E_Stop/ContextEstop.h"
#include "../../../header/FSMs/E_Stop/Idle.h"
#include "../../../header/FSMs/E_Stop/EStopActions.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/Hal/Sensors.h"
#include "../../../header/ChannelUtils.h"



ContextEstop::ContextEstop(int connectionID_Dispatcher, int connectionsID_FSM, ContextData *d){
	data = d;
	state = new Idle();
	a.connectionID_Dispatcher = connectionID_Dispatcher;
    a.connectionID_FSM = connectionsID_FSM;
    state->setActions(&a);
    state->setData(data);
}

ContextEstop::~ContextEstop(){
	delete state;
}

void ContextEstop::m1_reset_pressed(){
	state->m1_reset_pressed();
}
void ContextEstop::m1_estop_pressed(){
	state->m1_estop_pressed();
}
void ContextEstop::m1_estop_released(){
	state->m1_estop_released();
}
void ContextEstop::m2_reset_pressed(){
	state->m2_reset_pressed();
}
void ContextEstop::m2_estop_pressed(){
	state->m2_estop_pressed();
}
void ContextEstop::m2_estop_released(){
	state->m2_estop_released();
}