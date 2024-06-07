#include <sys/neutrino.h>
#include "../../../header/FSMs/E_Stop/EStopActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"

int connectionID_Dispatcher;
void EStopActions::sendMsg(int msg){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void EStopActions::turnRed(bool on){
    if(on){
        sendMsg(RED + LIGHT_ON);
    } else {
        sendMsg(RED + LIGHT_OFF);
    }

}
void EStopActions::turnYellow(bool on){
    if(on){
        sendMsg(YELLOW + LIGHT_ON);
    } else {
        sendMsg(YELLOW + LIGHT_OFF);
    }

}
void EStopActions::startRedFLASH(){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_ON, RED);
}
void EStopActions::stopRedFLASH(){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_OFF, RED);
}
void EStopActions::motorBlock(void){
    sendMsg(BLOCK);
}
void EStopActions::motorUnblock(void){
    sendMsg(UNBLOCK);
}
