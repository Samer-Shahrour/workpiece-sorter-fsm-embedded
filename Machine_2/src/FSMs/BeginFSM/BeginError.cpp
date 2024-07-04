#include "../../../header/FSMs/BeginFSM/BeginError.h"
#include "../../../header/FSMs/BeginFSM/BeginEstop.h"
#include "../../../header/FSMs/BeginFSM/wait_for_info.h"
void BeginError::error_ok() {
    new(this) Wait_for_info_Begin;
}
void BeginError::m1_estop_pressed() {
    new(this) BeginEstop;
}
void BeginError::m2_estop_pressed() {
    new(this) BeginEstop;
}
