#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"

#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"
#include "../../../header/FSMs/SwitchFSM/SwitchActions.h"
#include "../../../header/FSMs/SwitchFSM/SwitchError.h"
#include "../../../header/myTimer.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/FSMs/SwitchFSM/Wait_lbs.h"
#include <iostream>


#define TOLERANZ_MAX_C 600
#define TOLERANZ_MIN_B 650
#define TOLERANZ_MIN_D 1000


void handleWrongWP(SwitchActions *actions, ContextData* data, int id){
    if(data->chute_full){

        data->counter_Chute++;
        actions->letThrough();
        data->queue[id].startMaxTimer(data->sectionCticks+TOLERANZ_MAX_C);

    } else {
        data->queue[id].still_on_belt = false;

        actions->sortOut();
        data->queue[id].startMaxTimer(data->sectionDticks+TOLERANZ_MIN_D);
    }
}

void SwitchIdle::metal_detected(){
    int id = data->counter_switch;
    if(data->queue.size() > id && data->queue[id].getType() != WorkpieceType::Default) {
        data->queue[id].setType(WorkpieceType::MetalWorkpiece);
    }

}

void SwitchIdle::lbs_blocked() {
    int id = data->counter_switch;
    bool validId = id < data->queue.size();

    if(data->isStopped == true){
        printf("SWITCH: BELT IS STOPPED!");
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }

    if(!validId){
        printf("SWITCH: OUT OF BOUNDS [id: %d], [queueSize: %d}.\n", id, data->queue.size());
        actions->notifyFSMs();

        new(this) SwitchError;
        return;
    }

    if(data->queue[id].getType() == WorkpieceType::Default){
    	printf("SWITCH: WP SKIPPED HIGHTSENSOR [id: %d].\n", id);
		actions->notifyFSMs();

		new(this) SwitchError;
		return;
    }

    long long currentTimeStamp = createTimeStamp();
    long long timeUsed = currentTimeStamp - data->queue[id].minTimeStamp;
    bool wpTimerOk =  (timeUsed - data->queue[id].stopTime) >= (data->sectionBticks - TOLERANZ_MIN_B);
    std::cout << "SWITCH: timeUsed-stopTime: " << timeUsed - data->queue[id].stopTime << ", stopTime: " << data->queue[id].stopTime << " sectionBticks: " << data->sectionBticks - TOLERANZ_MIN_B << std::endl;
    data->queue[id].stopTime = 0;


    if(!wpTimerOk){
        printf("SWITCH: TOO EARLY: [id: %d].\n", id);
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }

    data->queue[id].minTimeStamp = createTimeStamp();
    data->queue[id].deleteMaxTimer();
    data->queue[id].switchStamp = true;
    data->counter_switch++;

    switch (data->queue[id].getType()) {
        case WorkpieceType::FlatWorkpiece:
            if(data->typCounter == 2){ //richtig
                data->typCounter%=2;
                data->counter_Chute++;
                data->queue[id].startMaxTimer(data->sectionCticks+TOLERANZ_MAX_C);
                actions->letThrough();
            } else { // falsch
                handleWrongWP(actions, data, id);
            }
            break;
        case WorkpieceType::MetalWorkpiece:
            if(data->typCounter < 2){ //richtig
                data->typCounter++;
                data->queue[id].startMaxTimer(data->sectionCticks+TOLERANZ_MAX_C);
                data->counter_Chute++;
                actions->letThrough();
            } else { // falsch
                handleWrongWP(actions, data, id);
            }
            break;
        default: // falsch
            handleWrongWP(actions, data, id);
            break;
    }
    new(this) Wait_lbs;
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
    int id = data->counter_Chute;
    bool validId = id < data->queue.size();

    data->chute_full = true;
    actions->turnYellow(true);

    if(data->isStopped){
        printf("CHUTE: BELT IS STOPPED!\n");
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }

    if(!validId || !data->queue[id].switchStamp){
        printf("CHUTE: OUT OF BOUNDS [id: %d], [queueSize: %d].\n", id, data->queue.size());
        actions->notifyFSMs();

        new(this) SwitchError;
        return;
    }


    data->queue[id].deleteMaxTimer();
    data->counter_Chute++;
    if(data->counter_Chute >= data->queue.size()){
        actions->motorStop();
    }


}

void SwitchIdle::lbc_free(){
    data->chute_full = false;
    actions->turnYellow(false);
}
