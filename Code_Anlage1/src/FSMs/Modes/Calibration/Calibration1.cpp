#include "../../../../header/FSMs/Modes/Calibration/Calibration1.h"
#include "../../../../header/FSMs/Modes/Calibration/Calibration2.h"
#include "../../../../header/FSMs/Modes/EstopModes.h"


void Wait_for_flat1::lbb_blocked(){
    actions->motor_start(true);
    actions->motor_fast(true);
    actions->startTickTimer(data);
    new(this) Measuring_Belt1;
}

void Wait_for_flat1::m1_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void Wait_for_flat1::m2_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void Measuring_Belt1::hight_changed(){
    actions->motor_fast(false);
    new(this) Hight_Measured1;
}

void Measuring_Belt1::incrementSection(){
    actions->incrementSection(&data->sectionAticks);
}

void Measuring_Belt1::m1_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void Measuring_Belt1::m2_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void Hight_Measured1::hight_changed(){
    actions->motor_fast(true);
    new(this) Measurement_Done1;
}

void Hight_Measured1::incrementSection(){
    actions->incrementSection(&data->slowHSticks);
    actions->incrementSection(&data->sectionBticks);
}

void Hight_Measured1::m1_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void Hight_Measured1::m2_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void Measurement_Done1::lbs_blocked(){
    actions->let_through(false);
    new(this) To_Chute;
}

void Measurement_Done1::incrementSection(){
    actions->incrementSection(&data->sectionBticks);
}

void Measurement_Done1::m1_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void Measurement_Done1::m2_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void To_Chute::lbc_blocked() {
    actions->motor_start(false);
    actions->deleteTimer(data);
    new(this) Wait_for_flat2;
}

void To_Chute::incrementSection() {
    actions->incrementSection(&data->sectionDticks);
}

void To_Chute::m1_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}

void To_Chute::m2_estop_pressed() {
    actions->stopGreenFLASH();
    new(this) EstopModes;
}
