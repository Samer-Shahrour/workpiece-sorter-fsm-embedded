#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"
#include "../../../header/FSMs/SwitchFSM/SwitchActions.h"
#include "../../../header/FSMs/SwitchFSM/SwitchError.h"
#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"
#include "../../../header/FSMs/SwitchFSM/Wait_lbs.h"

void Wait_lbs::lbs_free(){
    new(this) SwitchIdle;
}

void Wait_lbs::m2_estop_pressed() {
    new(this) SwitchEStop;
}
void Wait_lbs::m1_estop_pressed() {
    new(this) SwitchEStop;
}
void Wait_lbs::error() {
    new(this) SwitchError;
}

void Wait_lbs::lbc_blocked(){
    int id = 0;
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

    actions->motorStop();

    data->queue.clear();
}

void Wait_lbs::lbc_free(){
    data->chute_full = false;
    actions->turnYellow(false);
}

void Wait_lbs::metal_detected() {
}

