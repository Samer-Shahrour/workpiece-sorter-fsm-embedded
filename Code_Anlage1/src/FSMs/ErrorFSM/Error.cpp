#include "../../../header/FSMs/ErrorFSM/Error.h"
#include "../../../header/FSMs/ErrorFSM/EstopError.h"
#include "../../../header/FSMs/ErrorFSM/IdleError.h"
#include "../../../header/Logik/Workpiece.h"
void Error::reset_pressed() {

    actions->sendErrorOK();
    actions->stopRedFLASH();
    actions->motorUnblock();
    actions->turnGreen(true);
    data->queue.clear();
    data->counter_HM = 0;
    data->counter_switch = 0;
    resetGenerater();
    new(this) IdleError;
}

void Error::m1_estop_pressed() {
    new(this) EstopError;
}
void Error::m2_estop_pressed() {
    new(this) EstopError;
}
