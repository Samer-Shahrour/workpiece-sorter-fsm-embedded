#pragma once
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"

class Idle : public BaseStateEstop{
public:
	void m1_estop_pressed() override;
	void m2_estop_pressed() override;
	void m1_start_pressed() override;
	void m1_stop_pressed() override;
	void m1_lbb_blocked() override;
};
