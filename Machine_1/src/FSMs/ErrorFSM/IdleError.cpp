#include "../../../header/FSMs/ErrorFSM/Error.h"
#include "../../../header/FSMs/ErrorFSM/EstopError.h"
#include "../../../header/FSMs/ErrorFSM/IdleError.h"

void IdleError::error() {
    actions->turnAllOff();
    actions->startRedFLASH();
    actions->motorBlock();
    actions->motorStop();
    actions->deleteAllTimer(data);
    new(this) Error;
}

void IdleError::m1_estop_pressed() {
    new(this) EstopError;
}
void IdleError::m2_estop_pressed() {
    new(this) EstopError;
}
