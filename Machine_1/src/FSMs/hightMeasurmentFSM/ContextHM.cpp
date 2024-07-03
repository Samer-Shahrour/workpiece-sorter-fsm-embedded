
#include "../../../header/FSMs/hightMeasurmentFSM/ErrorHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/ContextHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/WaitForEncoder.h"
ContextHM::ContextHM(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d) {
	data = d;
    state = new WaitforEncoder();
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSM = connectionID_FSM;
    state->setActions(&actions);
    state->setData(d);
}

ContextHM::~ContextHM() {
    delete state;
}

void ContextHM::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextHM::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextHM::error_ok() {
    state->error_ok();
}

void ContextHM::error() {
    state->error();
}
void ContextHM::estop_ok(){
    state->estop_ok();
}
void ContextHM::hight_changed(int hight){
    state->hight_changed(hight);
}

