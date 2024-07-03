#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"
#include "../../../header/FSMs/E_Stop/EStopActions.h"

class ContextEstop {
private:
    BaseStateEstop *state;  // current state of state machine
    EStopActions a;
    ContextData *data;
public:
    ContextEstop(int connectionID_Dispatcher, int connectionID_FSM, ContextData *d);
    virtual ~ContextEstop();
    void m1_reset_pressed();
	void m1_estop_pressed();
	void m1_estop_released();
	void m2_reset_pressed();
	void m2_estop_pressed();
	void m2_estop_released();
	int connectionID_FSM;
};
