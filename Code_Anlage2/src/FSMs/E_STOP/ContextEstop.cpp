#include <sys/neutrino.h>
#include "../../../header/FSMs/E_Stop/ContextDataEstop.h"
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"
#include "../../../header/FSMs/E_Stop/ContextEstop.h"
#include "../../../header/FSMs/E_Stop/Idle.h"
#include "../../../header/FSMs/E_STOP/EStopActions.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/Hal/Sensors.h"
#include "../../../header/ChannelUtils.h"



ContextEstop::ContextEstop(int connectionID_Dispatcher){
	state = new Idle();
	a.connectionID_Dispatcher = connectionID_Dispatcher;
    state->setActions(&a);
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



void EStop_FSM_Thread(int channelID_FSM, int connectionID_Dispatcher){
    ThreadCtl(_NTO_TCTL_IO, 0);
    ContextEstop fsm(connectionID_Dispatcher);

    _pulse msg;
    bool receiveRunning = true;
    while(receiveRunning){
        int recvid = myReceivePulse(channelID_FSM, &msg);
        if (recvid > 0) {
            continue;
        }
        switch(msg.code){
            case PULSE_STOP_THREAD:
                printf("Dispatcher Thread kill code received!\n");
                receiveRunning = false;
                break;
            case PULSE_LOW_HIGH_MACHINE1:
                switch (msg.value.sival_int){
                    case E_STOP:
                        fsm.m1_estop_released();
                        break;
                    case BUTTON_RESET:
                        fsm.m1_reset_pressed();
                        break;
                }
                break;

            case PULSE_HIGH_LOW_MACHINE1:
                switch (msg.value.sival_int) {
                    case E_STOP:
                        fsm.m1_estop_pressed();
                        break;
                }
                break;

            case PULSE_LOW_HIGH_MACHINE2:
                switch (msg.value.sival_int) {
                    case E_STOP:
                        fsm.m2_estop_released();
                        break;
                    case BUTTON_RESET:
                        fsm.m2_reset_pressed();
                        break;
                }
                break;

            case PULSE_HIGH_LOW_MACHINE2:
                switch (msg.value.sival_int) {
                    case E_STOP:
                        fsm.m2_estop_pressed();
                        break;
                }
                break;

        }
    }
    printf("FSM Thread Done!\n");
}
