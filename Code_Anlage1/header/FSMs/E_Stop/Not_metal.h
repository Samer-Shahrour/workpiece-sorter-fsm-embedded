#pragma once
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"

class Not_metal : public BaseStateEstop{
public:
	void m1_estop_pressed() override;
	void m2_estop_pressed() override;
	void m1_start_pressed() override;
	void m1_stop_pressed() override;
	void m1_lbc_blocked() override;
};
