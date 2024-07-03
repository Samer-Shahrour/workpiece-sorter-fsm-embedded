#include "../../../header/FSMs/Modes/EstopModes.h"
#include "../../../header/FSMs/Modes/Operation.h"
void Operation::m1_estop_pressed(){
    new(this) EstopModes;
};

void Operation::m2_estop_pressed() {
    new(this) EstopModes;
}