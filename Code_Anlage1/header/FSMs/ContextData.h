#pragma once
#include <time.h>
#include <vector>
#include <list>
#include "../../header/Logik/Workpiece.h"

class ContextData{
private:

public:

    uint64_t sectionAticks = 0;
    uint64_t sectionBticks = 0;
    uint64_t sectionCticks = 0;
    uint64_t sectionDticks = 0;
    uint64_t stopTimeBegin = 0;
    uint64_t stopTime = 1;
    std::vector<Workpiece> queue;
    int counter_HM;
    uint64_t slowHSticks;
    int connectionID_FSM;
    timer_t timerStart_id; //Timer to check if START is pressed more then 1s
    uint64_t timerStart_reminingTime;

    //-------------Calibration-Timer----------//
    timer_t timer_FB;

    ContextData(){
        sectionAticks = 0;
        sectionBticks = 0;
        sectionCticks = 0;
        sectionDticks = 0;
        slowHSticks = 0;
        counter_HM = 0;
        connectionID_FSM = 0;
        timerStart_reminingTime = 0;
    }

    //-------------For Switch----------//
    int counter_switch = 0;
    bool chute_full = false;
    int typCounter = 0;         // for wp sequence
};
