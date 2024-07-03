    #include "BaseStateModes.h"
#include "ModesActions.h"
#include "../ContextData.h"

class ContextModes{
private:
    BaseStateModes *state;
    ModesActions actions;
    ContextData *data;
public:
    ContextModes(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d);
    virtual ~ContextModes();
    void m1_start_pressed();
    void m1_start_released();
    void estop_ok();
    void m1_estop_pressed();
    void m2_estop_pressed();
    void time_out_start();

    //for calibration
    void lbb_blocked();
    void lbb_free();
    void hight_changed();
    void lbs_blocked();
    void lbc_blocked();
    void lbe_blocked();
    void incrementSection();
};
