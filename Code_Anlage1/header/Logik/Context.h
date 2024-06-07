#include "../../header/Logik/BaseState.h"

void FSMThread(int, int);

class Context {
private:
    BaseState *state;  // current state of state machine
    ContextData data;
public:
    Context();
    virtual ~Context();
    void showState();
	void m1_stop_pressed();
	void m1_start_pressed();
    void m1_estop_pressed();
    void m1_estop_released();
    void m1_reset_pressed();
    void m2_estop_pressed();
    void m2_estop_released();
    /*
    void m1_lbb_blocked();
    void m1_lbb_free();
    void m1_lbs_blocked();
    void m1_lbs_free() ;
    void m1_lbc_blocked();
    void m1_lbc_free() ;
    void m1_lbe_blocked();
    void m1_lbe_free() ;
    void m1_start_pressed();
    void m1_start_released();
    void m1_stop_pressed();
    void m1_stop_released();
    void m1_reset_pressed();
    void m1_reset_released();
    void m1_estop_pressed();
    void m1_estop_released();
    void m1_in_hight_measurement();
    void m1_left_hight_measurement();
    void m1_metal_detected();
    */
    //Anlage 2
    /*
    void m2_lbc_blocked();
    void m2_lbc_free();
    void m2_lbe_blocked(); //-> wahrscheinlich nicht nötig
    void m2_lbe_free();
    void m2_start_pressed();
    void m2_start_released();
    void m2_estop_pressed() ;
    void m2_estop_released();
*/
};
