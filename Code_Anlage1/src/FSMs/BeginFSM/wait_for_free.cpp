#include "../../../header/FSMs/BeginFSM/wait_for_free.h"
#include "../../../header/FSMs/BeginFSM/wait_for_timer.h"
#include "../../../header/FSMs/BeginFSM/EstopBegin.h"
#include "../../../header/FSMs/BeginFSM/errorBegin.h"



void Wait_for_free::m1_lbb_free(){
	actions->startTimerBegin(data);
	actions->pushObject(data);
    new(this) Wait_for_timer;
}
void Wait_for_free::m1_estop_pressed() {
    new(this) EstopBegin;
}

void Wait_for_free::m2_estop_pressed() {
    new(this) EstopBegin;
}

void Wait_for_free::externer_error() {
    new(this) ErrorBegin;
}


