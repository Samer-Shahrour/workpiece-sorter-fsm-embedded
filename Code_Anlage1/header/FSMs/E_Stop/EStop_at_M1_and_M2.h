#pragma once
#include "../../../header/FSMs/E_Stop/BaseStateEstop.h"

class EStop_at_M1_and_M2 : public BaseStateEstop{
public:
	void m1_estop_released() override;
	void m2_estop_released() override;
};
