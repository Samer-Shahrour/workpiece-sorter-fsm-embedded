#include "../../../header/FSMs/SwitchFSM/MetalDetected.h"
#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"
#include "../../../header/FSMs/SwitchFSM/SwitchActions.h"
#include "../../../header/FSMs/SwitchFSM/SwitchError.h"
#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"

void MetalDetected::lbs_free(){
    printf("GO TO SWITCH IDLE \n");
    new(this) SwitchIdle;
}

void MetalDetected::m2_estop_pressed() {
    new(this) SwitchEStop;
}
void MetalDetected::m1_estop_pressed() {
    new(this) SwitchEStop;
}
void MetalDetected::error() {
    new(this) SwitchError;
}

void MetalDetected::lbc_blocked(){
    data->chute_full = true;
    actions->turnYellow(true);
}

void MetalDetected::lbc_free(){
    data->chute_full = false;
    actions->turnYellow(false);
}

void MetalDetected::metal_detected() {
    printf("metal detetcted from metal detected state \n");
}

