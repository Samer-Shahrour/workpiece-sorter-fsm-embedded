#include "../../../header/FSMs/SwitchFSM/SwitchError.h"
#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"
#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"


void SwitchError::error_ok() {
    new(this) SwitchIdle;
}

void SwitchError::m1_estop_pressed() {
    new(this) SwitchEStop;
}

void SwitchError::m2_estop_pressed() {
    new(this) SwitchEStop;
}

void SwitchError::lbc_blocked(){
    data->chute_full = true;
    actions->turnYellow(true);
}

void SwitchError::lbc_free(){
    data->chute_full = false;
    actions->turnYellow(false);
}

