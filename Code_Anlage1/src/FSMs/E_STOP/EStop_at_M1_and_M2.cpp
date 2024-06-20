#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1_and_M2.h"

void EStop_at_M1_and_M2::m2_estop_released(){
    new(this) EStop_at_M1;
}

void EStop_at_M1_and_M2::m1_estop_released(){
	new(this) EStop_at_M2;
}
