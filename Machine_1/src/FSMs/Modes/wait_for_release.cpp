#include "../../../header/FSMs/Modes/wait_for_release.h"
#include "../../../header/FSMs/Modes/Operation.h"
#include "../../../header/FSMs/Modes/EstopModes.h"
#include "../../../header/FSMs/Modes/Calibration/Calibration1.h"


void Wait_for_release::time_out_start(){
    actions->startGreenFLASH();
    actions->setCalibrationMode(true);
    data->sectionAticks = 0;
    data->sectionBticks = 0;
    data->sectionCticks = 0;
    data->sectionDticks = 0;
    new(this) Wait_for_flat1;
}

void Wait_for_release::m1_start_released(){
    //actions->deleteTimer(data);
    actions->stopGreenFLASH();
    actions->turnGreen(true);
    actions->setCalibrationMode(false);
    actions->turnLEDQ1(true);
    new(this) Operation;
}

void Wait_for_release::m1_estop_pressed(){
    new(this) EstopModes;
};

void Wait_for_release::m2_estop_pressed() {
    new(this) EstopModes;
}
