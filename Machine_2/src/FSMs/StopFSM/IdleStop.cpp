#include "../../../header/FSMs/StopFSM/IdleStop.h"
#include "../../../header/FSMs/StopFSM/Stop.h"
#include "../../../header/FSMs/StopFSM/EstopStop.h"
#include "../../../header/FSMs/StopFSM/StopError.h"
#include "../../../header/myTimer.h"

void IdleStop::stop_pressed() {
    actions->motorBlock();
    actions->getRemainingTime(data);
    actions->deleteAllTimer(data);
    for(int i = 0; i < data->queue.size(); i++){
        data->queue[i].tempStamp = createTimeStamp();
    }
    data->isStopped = true;
    new(this) Stop;
}
void IdleStop::m2_lbe_blocked() {
    new(this) StopError;
}
void IdleStop::m1_estop_pressed() {
    new(this) EstopStop;
}
void IdleStop::m2_estop_pressed() {
    new(this) EstopStop;
}

void IdleStop::error() {
	new(this) StopError;
}
