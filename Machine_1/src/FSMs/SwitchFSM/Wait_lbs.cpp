#include "../../../header/FSMs/SwitchFSM/Wait_lbs.h"

#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"
#include "../../../header/FSMs/SwitchFSM/SwitchActions.h"
#include "../../../header/FSMs/SwitchFSM/SwitchError.h"
#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"

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
    int id = data->counter_Chute;
    bool validId = id < data->queue.size();

    if(data->isStopped){
        printf("CHUTE: BELT IS STOPPED!\n");
        actions->notifyFSMs();
        new(this) SwitchError;
        return;
    }

    if(!validId){
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



    data->chute_full = true;
    actions->turnYellow(true);
}

void Wait_lbs::lbc_free(){
    data->chute_full = false;
    actions->turnYellow(false);
}

void Wait_lbs::metal_detected() {
}

