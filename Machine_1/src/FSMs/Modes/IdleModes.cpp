#include <iostream>
#include "../../../header/FSMs/Modes/IdleModes.h"
#include "../../../header/FSMs/Modes/wait_for_release.h"
#include "../../../header/FSMs/Modes/EstopModes.h"

void IdleModes::m1_start_pressed(){
    actions->startButtonTimer(data);
    new(this) Wait_for_release;
}

void IdleModes::m1_estop_pressed(){
    new(this) EstopModes;
}

void IdleModes::m2_estop_pressed() {
    new(this) EstopModes;
}

