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
    if(data->queue.size() > id && data->queue[id].minTimerOk) {
        data->queue[id].setType(WorkpieceType::MetalWorkpiece);
    }
    printf("SWITCH: METAL DETECTED: %d\n", id);
}

void SwitchIdle::lbs_blocked() {
    int id = data->counter_switch;
    if(data->queue.size() <= id || !data->queue[id].minTimerOk){ // WP aufgetaucht
        if(data->queue.size() <= id){
            printf("SWITCH: out of Bounds id: %d\n", id);
        }
        else if(!data->queue[id].minTimerOk){
            printf("SWITCH: minTimerOk_sectionB false: %d\n", id);
        }
        actions->notifyFSms();
        new(this) SwitchError;  // → brauchen wir höchstwahrscheinlich nicht,
                                // da notifyFSMs uns zu Error schickt, → müssen wir testen
        return;
    }
    data->queue[id].still_on_belt = false;
    //data->queue[id].minTimerOk = false;
    data->queue[id].deleteMaxTimer();
    //actions->deleteFromVector(data, id);
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

/*
void SwitchIdle::lbs_blocked() {

    if((data->queue[id].getType() == WorkpieceType::MetalWorkpiece) && (data->typCounter < 2)){
        //WP richtig (hohes mit metall)

        data->typCounter++;
        data->counter_switch++;
        actions->letThrough();
        //letThrough();
        myStartTimer(data->connectionID_FSM, PULSE_TIME_OUT_METAL_SWITCH, 0, false, timex);
        printf("SWITCH: letThrough RICHTIG METAL id: %d, typCounter: %d\n", id, data->typCounter);
        new(this) MetalDetected;
    }else if((data->queue[id].getType() == WorkpieceType::FlatWorkpiece) && (data->typCounter == 2)){ // richtiger fall
        // flat ist erwartet

        actions->letThrough();
        printf("typCounter before module: %d", data->typCounter);
        data->typCounter%=2;
        printf("typCounter after module: %d", data->typCounter);
        data->counter_switch++;

        myStartTimer(data->connectionID_FSM, PULSE_TIME_OUT_METAL_SWITCH, 0, false, timex);
        printf("SWITCH: letThrough RICHTIG FLAT id: %d, typCounter: %d\n", id, data->typCounter);
        new(this) MetalDetected;
    } else if((data->queue[id].getType() == WorkpieceType::MetalWorkpiece) && (data->typCounter == 2) && (data->chute_full)){
        //WP falsch (hohes mit metall but expected FlatWorkpiece)

        data->counter_switch++;
        actions->letThrough();
        //letThrough();
        myStartTimer(data->connectionID_FSM, PULSE_TIME_OUT_METAL_SWITCH, 0, false, timex);
        printf("SWITCH: letThrough FALSCH MEATL id: %d, typCounter: %d\n", id, data->typCounter);
        new(this) MetalDetected;

    } else if((data->queue[id].getType() == WorkpieceType::MetalWorkpiece) && (data->typCounter == 2) && (!data->chute_full)){
        //WP falsch (hohes mit metall but expected FlatWorkpiece)

        data->counter_switch++;
        actions->sortOut();
        //sortOut();
        myStartTimer(data->connectionID_FSM, PULSE_TIME_OUT_METAL_SWITCH, 0, false, timex);
        printf("SWITCH: sortOut FALSCH METAL id: %d, typCounter: %d\n", id, data->typCounter);
        new(this) MetalDetected;
    }

    else if((data->queue[id].getType() == WorkpieceType::FlatWorkpiece) && (data->typCounter < 2) && (!data->chute_full)){

        data->counter_switch++;
        actions->sortOut();
        //sortOut();
        printf("SWITCH: sortOut FALSCH FALT id: %d, typCounter: %d\n", id, data->typCounter);
        myStartTimer(data->connectionID_FSM, PULSE_TIME_OUT_METAL_SWITCH, 0, false, timex);
        new(this) MetalDetected;
    }
    else if((data->queue[id].getType()== WorkpieceType::FlatWorkpiece) && (data->typCounter < 2) && (data->chute_full)){

        data->counter_switch++;
        actions->letThrough();
        //letThrough();
        printf("SWITCH: letThrough FALSCH FLAT id: %d, typCounter: %d\n", id, data->typCounter);
        new(this) MetalDetected;
    } else if((data->queue[id].getType() != WorkpieceType::FlatWorkpiece) && (data->chute_full)){

        data->counter_switch++;
        actions->letThrough();
        //letThrough();
        printf("SWITCH: letThrough FALSCH FLAT id: %d, typCounter: %d\n", id, data->typCounter);
        myStartTimer(data->connectionID_FSM, PULSE_TIME_OUT_METAL_SWITCH, 0, false, timex);
        new(this) MetalDetected;
    } else if((data->queue[id].getType() != WorkpieceType::FlatWorkpiece) && (!data->chute_full)){

        data->counter_switch++;
        actions->sortOut();
        //updateAndSortOut();
        printf("SWITCH: letThrough FALSCH FLAT id: %d, typCounter: %d\n", id, data->typCounter);
        myStartTimer(data->connectionID_FSM, PULSE_TIME_OUT_METAL_SWITCH, 0, false, timex);
        new(this) MetalDetected;
    }
    else{
        printf("Nix LBS\n");
    }
}
 */

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
