#pragma once
#include "BaseStateHM.h"

class EstopHM : public BaseStateHM {
public:
    void estop_ok() override;
};
