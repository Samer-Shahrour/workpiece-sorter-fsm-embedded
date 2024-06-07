#pragma once
#include "../../header/Logik/BaseState.h"

class Start : public BaseState {
public:
	void showState() override;
	void m1_start_pressed() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override ;

};
