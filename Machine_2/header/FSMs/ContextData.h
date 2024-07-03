#pragma once
#include <time.h>
#include <vector>

#include "../../header/Logik/Workpiece.h"

class ContextData{
private:

public:
    //-------------Calibration-Timer----------//
    timer_t timer_FB;
    uint64_t sectionAticks = 0;
    uint64_t sectionBticks = 0;
    uint64_t sectionCticks = 0;
    uint64_t sectionDticks = 0;
    uint64_t stopTimeBegin = 0;
    bool isStopped = false;
    std::vector<Workpiece> queue;
    int connectionID_FSM;
    timer_t timerStart_id; //Timer to check if START is pressed more then 1s
    uint64_t timerStart_reminingTime;
    timer_t transfer_timer_id;
    uint64_t transfer_timer_remaining_time;

    bool isSwitch;

    ContextData(){
        sectionAticks = 0;
        sectionBticks = 0;
        sectionCticks = 0;
        sectionDticks = 0;
        connectionID_FSM = 0;
        timerStart_reminingTime = 0;
        typCounter = 0;
        chute_full = false;
        isStopped = false;
        transfer_timer_remaining_time = 0;
    }

    //-------------For Switch----------//
    bool chute_full = false;
    int typCounter = 0;         // for wp sequence
    //-------------For EndFSM----------//
};
