#pragma once
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"

class Wait_for_typ : public BaseStateEstop{
public:
	void m1_estop_pressed() override;
	void m2_estop_pressed() override;
	void m1_start_pressed() override;
	void m1_stop_pressed() override;
	void m1_lbs_blocked() override;
	void m1_metal_detected() override;
};
