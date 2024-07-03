#include "../../../header/FSMs/BeginFSM/wait_for_wp.h"
#include "../../../header/FSMs/BeginFSM/wait_for_free.h"
#include "../../../header/FSMs/BeginFSM/EstopBegin.h"
#include "../../../header/FSMs/BeginFSM/errorBegin.h"

void Wait_for_wp::m1_lbb_blocked() {
    actions->motorStart();
    actions->turnLEDQ1(false);
    new(this) Wait_for_free;
}

void Wait_for_wp::m1_estop_pressed() {
    new(this) EstopBegin;
}

void Wait_for_wp::m2_estop_pressed() {
    new(this) EstopBegin;
}
void Wait_for_wp::externer_error() {
    new(this) ErrorBegin;
}
