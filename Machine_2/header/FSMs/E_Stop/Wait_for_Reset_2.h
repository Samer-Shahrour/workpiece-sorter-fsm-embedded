#pragma once
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"

class Wait_for_Reset_2 : public BaseStateEstop{
public:
	void m1_estop_pressed() override;
	void m2_estop_pressed() override;
	void m2_reset_pressed() override;
};
