#include <iostream>
#include <time.h>
#include "../../../header/FSMs/hightMeasurmentFSM/WaitForEncoder.h"
#include "../../../header/FSMs/hightMeasurmentFSM/ErrorHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/UnderHS.h"
#include "../../../header/FSMs/hightMeasurmentFSM/EstopHM.h"
#include "../../../header/myTimer.h"

void WaitforEncoder::hight_changed(int _) {

    int id = data->counter_HM;
    bool validId = id < data->queue.size();

    if(data->stopTime == 0){
        printf("HM: BELT IS STOPPED!!!!!!!!!!");
        actions->notifyFSMs();
        new(this) ErrorHM;
    }

    if(!validId){
        printf("HM: OUT OF BOUNDS -id: %d, -queueSize: %d.\n", id, data->queue.size());
        actions->notifyFSMs();
        new(this) ErrorHM;
        return;
    }

    long long currentTimeStamp = createTimeStamp();
    uint64_t timeUsed = currentTimeStamp - data->queue[id].minTimeStamp;

    bool wpTimerOk =  (timeUsed - data->stopTime) >= (data->sectionAticks - 530);
    std::cout << "HM: timeUsed: " << timeUsed << " sectionAticks: " << data->sectionAticks - 350 << std::endl;

    if(!wpTimerOk){
        printf("HM: TOO EARLY: -id:%d.\n", id);
        actions->notifyFSMs();
        new(this) ErrorHM;
        return;
    }

    actions->motor_fast(false);
    actions->getRemainingTime(data, id);
    actions->deleteAllTimer(data);
    actions->restartMaxTimer(data, id);
    actions->incrementSwitchTime();
    //start Timer for Section B
    data->queue[id].minTimeStamp = createTimeStamp();
    data->queue[id].startMaxTimer(data->sectionBticks+500);
    new(this) UnderHS;

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


