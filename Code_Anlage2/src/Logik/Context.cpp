#include <sys/neutrino.h>
#include "../../header/PulseCodes.h"
#include "../../header/Logik/Context.h"
#include "../../header/FSM_States/start.h"
#include "../../header/hal/Sensors.h"
#include "../../header/ChannelUtils.h"

using namespace std;

void FSMThread(int channelID_FSM_ESTOP, int connectionID_Dispatcher){
    ThreadCtl(_NTO_TCTL_IO, 0);
    Context fsm;

    _pulse msg;
    bool receiveRunning = true;
    while(receiveRunning){
        int recvid = myReceivePulse(channelID_FSM_ESTOP, &msg);
        if (recvid > 0) {
            continue;
        }
        switch(msg.code){
            case PULSE_STOP_THREAD:
                printf("Dispatcher Thread kill code received!\n");
                receiveRunning = false;
                break;
            case PULSE_LOW_HIGH_MACHINE1:

                switch (msg.value.sival_int) {
                    case BUTTON_START:
                        fsm.m1_start_pressed();
                            break;
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
                    case BUTTON_STOP:
                        fsm.m1_stop_pressed();
                            break;
                    case E_STOP:
                        fsm.m1_estop_pressed();
                            break;
                }

                break;

            case PULSE_LOW_HIGH_MACHINE2:
            	printf("Anlage 1 msg received from Anlage2 \n");
                switch (msg.value.sival_int) {
                    case E_STOP:
                        fsm.m2_estop_released();
                        break;
                    case BUTTON_RESET:
                        fsm.m1_reset_pressed();
                        break;

                }
                break;

            case PULSE_HIGH_LOW_MACHINE2:
            	printf("Anlage 1 msg received from Anlage2 \n");
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

Context::Context() {
    state = new Start();
    state->setData(&data);
}

Context::~Context() {
    delete state;
}

void Context::m1_stop_pressed(){
	state->m1_stop_pressed();
}

void Context::m1_start_pressed(){
	state->m1_start_pressed();
}

void Context::m1_estop_pressed(){
    state->m1_estop_pressed();
}

void Context::m1_estop_released(){
    state->m1_estop_released();
}

void Context::m2_estop_pressed(){
    state->m2_estop_pressed();
}

void Context::m2_estop_released(){
    state->m2_estop_released();
}

void Context::m1_reset_pressed(){
    state->m1_reset_pressed();
}
/*
void Context::m1_lbb_blocked(){
    state->m1_lbb_blocked();
    state->showState();
}

void Context::m1_lbb_free(){
    state->m1_lbb_free();
    state->showState();
}

void Context::m1_lbs_blocked(){
    state->m1_lbs_blocked();
    state->showState();
}

void Context::m1_lbs_free(){
    state->m1_lbs_free();
    state->showState();
}

void Context::m1_lbc_blocked(){
    state->m1_lbc_blocked();
    state->showState();
}

void Context::m1_lbc_free(){
    state->m1_lbc_free();
    state->showState();
}

void Context::m1_lbe_blocked(){
    state->m1_lbe_blocked();
    state->showState();
}

void Context::m1_lbe_free(){
    state->m1_lbe_free();
    state->showState();
}

void Context::m1_start_pressed(){
    state->m1_start_pressed();
    state->showState();
}

void Context::m1_start_released(){
    state->m1_stop_released();
    state->showState();
}

void Context::m1_stop_pressed(){
    state->m1_stop_pressed();
    state->showState();
}

void Context::m1_stop_released(){
    state->m1_stop_released();
    state->showState();
}

void Context::m1_reset_pressed(){
    state->m1_reset_pressed();
    state->showState();
}

void Context::m1_reset_released(){
    state->m1_reset_released();
    state->showState();
}

void Context::m1_estop_pressed(){
    state->m1_estop_pressed();
    state->showState();
}

void Context::m1_estop_released(){
    state->m1_estop_released();
    state->showState();
}

void Context::m1_in_hight_measurement(){
    state->m1_in_hight_measurement();
    state->showState();
}

void Context::m1_left_hight_measurement(){
    state->m1_left_hight_measurement();
    state->showState();
}

void Context::m1_metal_detected(){
    state->m1_metal_detected();
    state->showState();
}
*/
/*
//Anlage 2
void Context::m2_lbc_blocked(){
    state->m2_lbc_blocked();
}

void Context::m2_lbc_free(){
    state->m2_lbc_free();
}

void Context::m2_lbe_blocked(){ //-> wahrscheinlich nicht nötig
    state->m2_lbe_blocked();
}

void Context::m2_lbe_free(){
    state->m2_lbe_free();
}

void Context::m2_start_pressed(){
    state->m2_start_pressed();
}

void Context::m2_start_released(){
    state->m2_start_released();
}

void Context::m2_estop_pressed(){
    state->m2_estop_pressed();
}

void Context::m2_estop_released(){
    state->m2_estop_released();
}
 */
