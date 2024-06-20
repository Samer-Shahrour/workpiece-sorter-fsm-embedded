#include "../../../header/FSMs/StopFSM/Stop.h"
#include "../../../header/FSMs/StopFSM/EstopStop.h"
#include "../../../header/FSMs/StopFSM/IdleStop.h"
#include "../../../header/FSMs/StopFSM/StopError.h"
#include "../../../header/myTimer.h"

void Stop::start_pressed() {
    actions->restartAllTimer(data);
    actions->motorUnblock();
    data->stopTime = createTimeStamp() - data->stopTimeBegin;
    data->stopTimeBegin = 0;
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
