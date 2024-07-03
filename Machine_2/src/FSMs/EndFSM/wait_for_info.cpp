
#include "../../../header/FSMs/EndFSM/wait_for_info.h"
#include "../../../header/FSMs/EndFSM/endError.h"
#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/wait_for_gone.h"
#include "../../../header/myTimer.h"
#include "../../../header/variables.h"

#define TOLERANZ 500

void Wait_for_info_End::m2_lbe_blocked() {
    int id = 0;
    bool validId = id < data->queue.size();
    if(data->isStopped){
        printf("END: BELT IS STOPPED!\n");
        actions->notifyFSMs();
        new(this) EndError;
    }
    if(!validId){
        printf("SWITCH: OUT OF BOUNDS -id: %d, -queueSize: %d.\n", id, data->queue.size());
        actions->notifyFSMs();
        new(this) EndError;
        return;
    }
    if(data->queue[id].getType() == WorkpieceType::Default
			|| !data->queue[id].switchStamp){
		printf("End: WP SKIPPED SENSOR(s).\n");
		actions->notifyFSMs();
		new(this) EndError;
		return;
	}

    long long currentTimeStamp = createTimeStamp();
    uint64_t timeUsed = currentTimeStamp - data->queue[id].minTimeStamp;

    bool wpTimerOk =  (timeUsed - data->queue[id].stopTime) >= (data->sectionCticks - TOLERANZ);
    std::cout << "END: timeUsed: " << timeUsed - data->queue[id].stopTime << " sectionAticks: " << data->sectionAticks - TOLERANZ << std::endl;

    if(!wpTimerOk){
        printf("END: TOO EARLY\n");
        actions->notifyFSMs();
        new(this) EndError;
        return;
    }



    actions->deleteMaxTimer(data);
    actions->motorBlock();
    new(this) Wait_for_gone;
}


void Wait_for_info_End::m1_estop_pressed() {
    new(this) EndEstop;
}

void Wait_for_info_End::m2_estop_pressed() {
    new(this) EndEstop;
}

void Wait_for_info_End::error() {
    new(this) EndError;
}
