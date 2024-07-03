#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/endIdle.h"
#include "../../../header/FSMs/EndFSM/endActions.h"
#include "../../../header/FSMs/EndFSM/endError.h"
#include "../../../header/FSMs/EndFSM/m2_free.h"
#include "../../../header/FSMs/EndFSM/m2_not_free.h"
#include "../../../header/myTimer.h"

#define TOLERANZ 700

void EndIdle::m1_estop_pressed() {
	new(this) EndEstop;
}
void EndIdle::m2_estop_pressed(){
	new(this) EndEstop;
}
void EndIdle::m1_lbe_blocked(){

	bool validID = true;

    for(int i = data->counter_End; i <= data->queue.size(); i++){
    	if(i == data->queue.size()){
			validID = false;
			break;
		}
        if(data->queue[i].still_on_belt){
            data->counter_End = i;
            break;
        }
    }
    if(!validID){
        printf("End: Out of Bound!.\n");
        actions->notifyFSMs();
        new(this) EndError;
        return;
    }
    int id = data->counter_End;

    if(data->queue[id].getType() == WorkpieceType::Default
    		|| !data->queue[id].switchStamp){
    	printf("End: WP SKIPPED SENSOR(s).\n");
		actions->notifyFSMs();
		new(this) EndError;
		return;
    }
    long long currentTimeStamp = createTimeStamp();
    uint64_t timeUsed = currentTimeStamp - data->queue[id].minTimeStamp;

    bool wpTimerOk =  true;
    std::cout << "END: time Used: " << timeUsed-data->queue[id].stopTime << " time Expected in Section C: " << data->sectionCticks - TOLERANZ << std::endl;
    data->queue[id].stopTime = 0;
    if(!wpTimerOk){
        printf("END: TOO EARLY: -id:%d.\n", id);
        actions->notifyFSMs();
        new(this) EndError;
        return;
    }
	if(data->isStopped){
		printf("END: BELT IS STOPPED!");
		actions->notifyFSMs();
		new(this) EndError;
		return;
	}
    data->queue[id].still_on_belt = false;
    data->queue[id].deleteMaxTimer();
	if(data->m2_free) {
        actions->sendMsgTOM2(data, id);
        data->m2_free = false;
        new (this) M2_free;
    }
    else if(!data->m2_free){
        actions->motor_block();
        actions->getRemainingTime(data);
        actions->deleteAllTimer(data);
        new (this) M2_not_free;
    }
}
void EndIdle::m2_Ok() {
    data->m2_free = true;
}

void EndIdle::m2_Nok() {
    data->m2_free = false;
}

void EndIdle::error() {
    new(this) EndError;
}

