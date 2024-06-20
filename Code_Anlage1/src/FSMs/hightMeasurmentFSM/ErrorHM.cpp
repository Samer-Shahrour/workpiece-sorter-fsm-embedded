#include "../../../header/FSMs/hightMeasurmentFSM/ErrorHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/EstopHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/WaitForEncoder.h"
void ErrorHM::error_ok() {
    actions->motor_fast(true);
    new(this) WaitforEncoder;
}
void ErrorHM::m1_estop_pressed() {
    new(this) EstopHM;
}
void ErrorHM::m2_estop_pressed() {
    new(this) EstopHM;
}
