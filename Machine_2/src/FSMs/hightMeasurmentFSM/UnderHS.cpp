#include "../../../header/FSMs/hightMeasurmentFSM/UnderHS.h"
#include "../../../header/FSMs/hightMeasurmentFSM/WaitForEncoder.h"
#include "../../../header/FSMs/hightMeasurmentFSM/EstopHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/HMActions.h"
#include "../../../header/FSMs/hightMeasurmentFSM/ErrorHM.h"

void UnderHS::hight_changed(int hight){

    actions->motor_fast(true);
    actions->setWpType(data, hight);
    if(actions->checkWpType(data)){
        new(this) WaitforEncoder;
    } else {
        printf("FEHLER HM: typ stimmt nicht über ein!\n");
        actions->notifyFSMs();
        new(this) ErrorHM;
    }
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
