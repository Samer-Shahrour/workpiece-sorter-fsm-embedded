#pragma once
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"

class Idle : public BaseStateEstop{
public:
	void m1_estop_pressed() override;
	void m2_estop_pressed() override;
};
