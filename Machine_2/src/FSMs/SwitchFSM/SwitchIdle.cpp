#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"

#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"
#include "../../../header/FSMs/SwitchFSM/SwitchActions.h"
#include "../../../header/FSMs/SwitchFSM/SwitchError.h"
#include "../../../header/myTimer.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/variables.h"
#include <iostream>

#include "../../../header/FSMs/SwitchFSM/Wait_lbs.h"

#define TOLERANZ 320
#define TOLERANZ_MIN_D 1000
#define TOLERANZ_MAX_D 1000
void SwitchIdle::handleWrongWP( ContextData* data){
    if(data->chute_full){
        printf("SWITCH: Rutsche voll");
        actions->notifyFSMs();
        new(this) SwitchError;
    } else {
        data->queue[0].startMaxTimer(data->sectionDticks+TOLERANZ_MAX_D);
        actions->sortOut();
    }
}

void SwitchIdle::metal_detected(){
    int id = FIRST_ITEM;
    if(data->queue.size() > id && data->queue[id].getType() != WorkpieceType::Default) {
        data->queue[id].setType(WorkpieceType::MetalWorkpiece);
    }
}

void SwitchIdle::lbs_blocked() {
    int id = FIRST_ITEM;
    bool validId = id < data->queue.size();

    if(data->isStopped){
        printf("SWITCH: BELT IS STOPPED!");
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }

    if(!validId){
        printf("SWITCH: OUT OF BOUNDS -id: %d, -queueSize: %d.\n", id, data->queue.size());
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
    bool wpTimerOk =  (timeUsed - data->queue[id].stopTime) >= (data->sectionBticks - TOLERANZ);
    std::cout << "SWITCH: timeUsed: " << timeUsed - data->queue[id].stopTime<< " STOPTIME: "<< data->queue[id].stopTime << " sectionBticks: " << data->sectionBticks - TOLERANZ << std::endl;

    if(!wpTimerOk){
        printf("SWITCH: TOO EARLY: -id:%d.\n", id);
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }

    if(data->queue[id].type_received_from_m1 != data->queue[id].getType()){
        actions->notifyFSMs();
        printf("FEHLER SWITCH: typ stimmt nicht über ein!\n");
        new(this) SwitchError;
    }


    data->queue[id].minTimeStamp = createTimeStamp();
    data->queue[id].still_on_belt = false;
    data->queue[id].deleteMaxTimer();
    data->queue[id].switchStamp = true;


    switch (data->queue[id].getType()) {
        case WorkpieceType::FlatWorkpiece:
            if(data->typCounter == 2){ //richtig
                data->typCounter%=2;
                data->queue[id].startMaxTimer(data->sectionCticks+TOLERANZ);
                actions->letThrough();
            } else { // falsch
                handleWrongWP( data);
            }
            break;
        case WorkpieceType::MetalWorkpiece:
            if(data->typCounter < 2){ //richtig
                data->typCounter++;
                data->queue[id].startMaxTimer(data->sectionCticks+TOLERANZ);
                actions->letThrough();
            } else { // falsch
                handleWrongWP( data);
            }
            break;
        default: // falsch
            handleWrongWP( data);
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
    int id = 0;
    bool validId = id < data->queue.size();

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
    actions->motorStop();
    data->chute_full = true;
    actions->turnYellow(true);
    data->queue.clear();
}

void SwitchIdle::lbc_free(){
    data->chute_full = false;
    actions->turnYellow(false);
}
