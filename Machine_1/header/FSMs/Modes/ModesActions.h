#pragma once
#include <time.h>
#include "../../../header/FSMs/ContextData.h"



class ModesActions{

private:
    void sendMsg(int);

public:
    int connectionID_Dispatcher;

    void startButtonTimer(ContextData* data);
    void deleteTimer(ContextData* data);
    void startTickTimer(ContextData* data);

    //----------------------Modes-Actions----------------------//

    void turnGreen(bool);
    void turnLEDQ1(bool);
    void stopGreenFLASH();
    void startGreenFLASH();

    //----------------------Calibration-Actions----------------------//

    void motor_fast(bool);
    void let_through(bool);
    void motor_start(bool);

    void incrementSection(uint64_t* section);
    void setCalibrationMode(bool);
};
