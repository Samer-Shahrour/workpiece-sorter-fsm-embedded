#include "../../../header/FSMs/E_Stop/ContextDataEstop.h"
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"
#include "../../../header/FSMs/E_Stop/EStopActions.h"

void EStop_FSM_Thread(int channelID_FSM, int connectionID_Dispatcher);

class ContextEstop {
private:
    BaseStateEstop *state;  // current state of state machine
    EStopActions a;
public:
    ContextEstop(int connectionID_Dispatcher);
    virtual ~ContextEstop();
    void m1_reset_pressed();
	void m1_estop_pressed();
	void m1_estop_released();
	void m2_reset_pressed();
	void m2_estop_pressed();
	void m2_estop_released();

	void m1_lbb_blocked();
	void m1_lbb_free();

	void m1_lbs_blocked();
	void m1_lbs_free();

	void m1_lbc_blocked();

	void m1_lbe_blocked();
	void m1_lbe_free();

	void m1_start_pressed();
	void m1_stop_pressed();

	void m1_metal_detected();
};
