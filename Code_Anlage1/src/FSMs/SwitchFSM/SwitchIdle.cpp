#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"

#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"
#include "../../../header/FSMs/SwitchFSM/SwitchActions.h"
#include "../../../header/FSMs/SwitchFSM/SwitchError.h"
#include "../../../header/FSMs/SwitchFSM/MetalDetected.h"
#include "../../../header/myTimer.h"
#include "../../../header/PulseCodes.h"
#include <iostream>

void handleWrongWP(SwitchActions *actions, ContextData* data){
    if(data->chute_full){
        printf("wird durch gelassen \n");
        actions->letThrough();
    } else {
        printf("wird aussortiert \n");
        actions->sortOut();
    }
}

void SwitchIdle::metal_detected(){
    int id = data->counter_switch;
    if(data->queue.size() > id) {
        data->queue[id].setType(WorkpieceType::MetalWorkpiece);
    }
    printf("SWITCH: METAL DETECTED: %d\n", id);
}

void SwitchIdle::lbs_blocked() {
    int id = data->counter_switch;
    bool validId = id < data->queue.size();

    if(data->stopTime == 0){
        printf("SWITCH: BELT IS STOPPED!!!!!!!!!!");
        actions->notifyFSMs();
        new(this) SwitchError;
    }

    if(!validId){
        printf("SWITCH: OUT OF BOUNDS -id: %d, -queueSize: %d.\n", id, data->queue.size());
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }

    long long currentTimeStamp = createTimeStamp();
    long long timeUsed = currentTimeStamp - data->queue[id].minTimeStamp;
    bool wpTimerOk =  (timeUsed - data->stopTime) >= (data->sectionBticks - 280);
    std::cout << "HM: timeUsed: " << timeUsed << " sectionAticks: " << data->sectionBticks - 220 << std::endl;

    if(!wpTimerOk){
        printf("SWITCH: TOO EARLY: -id:%d.\n", id);
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }



    data->queue[id].minTimeStamp = createTimeStamp();
    data->queue[id].still_on_belt = false;
    data->queue[id].deleteMaxTimer();
    data->counter_switch++;

    switch (data->queue[id].getType()) {
        case WorkpieceType::FlatWorkpiece:
            if(data->typCounter == 2){ //richtig
                data->typCounter%=2;
                printf("Richtiges FLACH WP\n");
                actions->letThrough();
            } else { // falsch
                printf("Falsches FLACH WP "); //bewusst kein '\n'
                handleWrongWP(actions, data);
            }
            break;
        case WorkpieceType::MetalWorkpiece:
            if(data->typCounter < 2){ //richtig
                data->typCounter++;
                printf("Richtiges METAL WP\n");
                actions->letThrough();
            } else { // falsch
                printf("Falsches METAL WP ");
                handleWrongWP(actions, data);
            }
            break;
        default: // falsch
            printf("Falsches DEFEKT WP ");
            handleWrongWP(actions, data);
            break;
    }
    new(this) MetalDetected;
}

void SwitchIdle::error(){
    new(this) SwitchError;
}

void SwitchIdle::m2_estop_pressed() {
    new(this) SwitchEStop;
}

void SwitchIdle::m1_estop_pressed() {
    new(this) SwitchEStop;
}

void SwitchIdle::lbc_blocked(){
    data->chute_full = true;
    actions->turnYellow(true);
}

void SwitchIdle::lbc_free(){
    data->chute_full = false;
    actions->turnYellow(false);
}
