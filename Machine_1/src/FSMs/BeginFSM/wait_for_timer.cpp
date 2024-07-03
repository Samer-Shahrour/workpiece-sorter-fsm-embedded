#include "../../../header/FSMs/BeginFSM/wait_for_timer.h"
#include "../../../header/FSMs/BeginFSM/wait_for_wp.h"
#include "../../../header/FSMs/BeginFSM/wait_for_free.h"
#include "../../../header/FSMs/BeginFSM/EstopBegin.h"
#include "../../../header/FSMs/BeginFSM/errorBegin.h"
#include <stdio.h>

void Wait_for_timer::m1_lbb_blocked() {
	printf("ERROR: min. Abstand nicht eingehalten\n");
    actions->notifyFSMs();
    actions->turnLEDQ1(false);
    new(this) ErrorBegin;
}

void Wait_for_timer::time_out_begin() {
    actions->turnLEDQ1(true);
    new(this) Wait_for_wp;
}

void Wait_for_timer::externer_error() {
    new(this) ErrorBegin;
}

void Wait_for_timer::m1_estop_pressed() {
    new(this) EstopBegin;
}

void Wait_for_timer::m2_estop_pressed() {
    new(this) EstopBegin;
}

