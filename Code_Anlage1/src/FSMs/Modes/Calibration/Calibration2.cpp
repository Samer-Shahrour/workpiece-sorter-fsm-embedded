
#include "../../../../header/FSMs/Modes/Calibration/Calibration2.h"
#include "../../../../header/FSMs/Modes/Calibration/Calibration1.h"
#include "../../../../header/FSMs//Modes/IdleModes.h"
#include "../../../../header/FSMs/Modes/EstopModes.h"


/* Wait for fals2  */
void Wait_for_flat2 ::lbb_blocked(){
    actions->motor_start(true);
    actions->motor_fast(true);
    //actions->startTickTimer(data);
    new (this) Measuring_Belt2;
}

void Wait_for_flat2 ::m1_estop_pressed(){
    actions->stopGreenFLASH();
    new (this) EstopModes;
}

void Wait_for_flat2 ::m2_estop_pressed(){
    actions->stopGreenFLASH();
    new (this) EstopModes;
}

/* Measuring Belt2 */
void Measuring_Belt2::hight_changed() {
    actions->motor_fast(false);
    new (this) Hight_Measured2;
}
void Measuring_Belt2::m1_estop_pressed() {
    actions->stopGreenFLASH();
    new (this) EstopModes;
}
void Measuring_Belt2::m2_estop_pressed() {
    actions->stopGreenFLASH();
    new (this) EstopModes;
}

void Hight_Measured2::hight_changed() {
    actions->motor_fast(true);
    new (this) Measurement_Done2;
}
void Hight_Measured2::m1_estop_pressed(){
    actions->stopGreenFLASH();
    new (this) EstopModes;
}

void Hight_Measured2::m2_estop_pressed(){
    actions->stopGreenFLASH();
    new (this) EstopModes;
}
/* Measurement_Done2  */
void Measurement_Done2::lbs_blocked() { //lehmann hat grade von mqtt mosquito gesprochen
    actions->startTickTimer(data);
    actions->let_through(true);
    new (this) Let_Through;

}
void Measurement_Done2::m1_estop_pressed() {
    actions->stopGreenFLASH();
    new (this) EstopModes;

}
void Measurement_Done2::m2_estop_pressed(){
    actions->stopGreenFLASH();
    new (this) EstopModes;
}
/* Let_Through */
void Let_Through::lbe_blocked(){
    actions->deleteTimer(data);
    actions->stopGreenFLASH();
    actions->turnGreen(false);
    actions->motor_start(false);

    std::cout << "sectionA: " << data->sectionAticks << std::endl;
    std::cout << "sectionB: " << data->sectionBticks << std::endl;
    std::cout << "sectionC: " << data->sectionCticks << std::endl;
    std::cout << "sectionD: " << data->sectionDticks << std::endl;

    new (this) IdleModes;
}

void Let_Through::incrementSection() {
    actions->incrementSection(&data->sectionCticks);
}
void Let_Through::m1_estop_pressed(){
    actions->stopGreenFLASH();
    new (this) EstopModes;
}
void Let_Through ::m2_estop_pressed(){
    actions->stopGreenFLASH();
    new (this) EstopModes;
}
