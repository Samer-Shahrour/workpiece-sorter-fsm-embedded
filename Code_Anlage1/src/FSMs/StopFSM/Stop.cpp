#include "../../../header/FSMs/StopFSM/Stop.h"
#include "../../../header/FSMs/StopFSM/EstopStop.h"
#include "../../../header/FSMs/StopFSM/IdleStop.h"
#include "../../../header/FSMs/StopFSM/StopError.h"

void Stop::start_pressed() {
    actions->restartAllTimer(data);
    actions->motorUnblock();
    new(this) IdleStop;
}

void Stop::m1_estop_pressed() {
    new(this) EstopStop;
}
void Stop::m2_estop_pressed() {
    new(this) EstopStop;
}

void Stop::error() {
	new(this) StopError;
}
