#include <iostream>
#include "../../../header/FSMs/hightMeasurmentFSM/WaitForEncoder.h"
#include "../../../header/FSMs/hightMeasurmentFSM/ErrorHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/UnderHS.h"
#include "../../../header/FSMs/hightMeasurmentFSM/EstopHM.h"
#include "../../../header/myTimer.h"

void WaitforEncoder::hight_changed(int _) {
    int id = data->counter_HM;
    bool wsTimerOk = data->queue[id].minTimerOk;
    bool validId = id < data->queue.size();

    if(validId && wsTimerOk){
        //data->queue[id].minTimerOk = false; // thread setzt die variable auf true wenn der time event da ist
        actions->motor_fast(false);
        actions->getRemainingTime(data, id);
        actions->deleteAllTimer(data);
        actions->restartMaxTimer(data, id);
        actions->incrementSwitchTime();
        //actions->startTimer(data, id); //for next section (B)
        new(this) UnderHS;
    } else {
        if(!validId){
            printf("id falsch: %d --- queueSize: %d\n", id, data->queue.size());
        }
        else if(!wsTimerOk){
            printf("minTimerOk false: id:%d ", id);
            std::cout << "remaining Time: " << getRemainingTimeInMS(data->queue[id].min_time) << std::endl;
        }
        actions->notifyFSMs();
        //keine timer delete, error fsm macht das
        new(this) ErrorHM;
    }
}

void WaitforEncoder::m2_estop_pressed() {
    new(this) EstopHM;
}
void WaitforEncoder::m1_estop_pressed() {
    new(this) EstopHM;
}
void WaitforEncoder::error() {
    new(this) ErrorHM;
}


