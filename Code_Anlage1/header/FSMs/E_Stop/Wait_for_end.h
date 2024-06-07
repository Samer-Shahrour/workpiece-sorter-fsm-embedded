#pragma once
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"

class Wait_for_end : public BaseStateEstop{
public:
	void m1_estop_pressed() override;
	void m2_estop_pressed() override;
	void m1_start_pressed() override;
	void m1_stop_pressed() override;
	void m1_lbe_free() override;
};
