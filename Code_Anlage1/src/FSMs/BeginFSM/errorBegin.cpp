#include "../../../header/FSMs/BeginFSM/errorBegin.h"
#include "../../../header/FSMs/BeginFSM/wait_for_wp.h"
#include "../../../header/FSMs/BeginFSM/EstopBegin.h"


void ErrorBegin::error_ok() {
    actions->turnLEDQ1(true);

    new(this) Wait_for_wp;
}

void ErrorBegin::m1_estop_pressed() {
    new(this) EstopBegin;
}

void ErrorBegin::m2_estop_pressed() {
    new(this) EstopBegin;
}
