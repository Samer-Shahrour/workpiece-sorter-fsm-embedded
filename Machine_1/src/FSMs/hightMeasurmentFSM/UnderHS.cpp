#include "../../../header/FSMs/hightMeasurmentFSM/UnderHS.h"
#include "../../../header/FSMs/hightMeasurmentFSM/WaitForEncoder.h"
#include "../../../header/FSMs/hightMeasurmentFSM/EstopHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/HMActions.h"
#include "../../../header/FSMs/hightMeasurmentFSM/ErrorHM.h"

void UnderHS::hight_changed(int hight){
    int id = data->counter_HM;
    actions->motor_fast(true);
    actions->setWpType(data, id, hight);
    data->counter_HM++;
    new(this) WaitforEncoder;
}
void UnderHS::m2_estop_pressed() {
    new(this) EstopHM;
}
void UnderHS::m1_estop_pressed() {
    new(this) EstopHM;
}
void UnderHS::error() {
    new(this) ErrorHM;
}
