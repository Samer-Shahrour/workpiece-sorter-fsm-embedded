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


void ContextEstop::m1_lbb_blocked(){
	state->m1_lbb_blocked();
}

void ContextEstop::m1_lbb_free(){
	state->m1_lbb_free();
}

void ContextEstop::m1_lbs_blocked(){
	state->m1_lbs_blocked();
}
void ContextEstop::m1_lbs_free(){
	state->m1_lbs_free();
}

void ContextEstop::m1_lbc_blocked(){
	state->m1_lbc_blocked();
}

void ContextEstop::m1_lbe_blocked(){
	state->m1_lbe_blocked();
}
void ContextEstop::m1_lbe_free(){
	state->m1_lbe_free();
}

void ContextEstop::m1_start_pressed(){
	state->m1_start_pressed();
}
void ContextEstop::m1_stop_pressed(){
	state->m1_stop_pressed();
}

void ContextEstop::m1_metal_detected(){
	state->m1_metal_detected();
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
                    case BUTTON_START:
						fsm.m1_start_pressed();
						break;
                    case LBB:
                    	fsm.m1_lbb_free();
                    	break;
                    case LBS:
						fsm.m1_lbs_free();
						break;
                    case LBE:
						fsm.m1_lbe_free();
						break;
                    case SENSOR_METAL:
                    	fsm.m1_metal_detected();
                    	break;
                }
                break;

            case PULSE_HIGH_LOW_MACHINE1:
                switch (msg.value.sival_int) {
                    case E_STOP:
                        fsm.m1_estop_pressed();
                        break;
                    case BUTTON_STOP:
                    	fsm.m1_stop_pressed();
                    	break;
                    case LBB:
						fsm.m1_lbb_blocked();
						break;
					case LBC:
						fsm.m1_lbc_blocked();
						break;
					case LBS:
						fsm.m1_lbs_blocked();
						break;
					case LBE:
						fsm.m1_lbe_blocked();
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
