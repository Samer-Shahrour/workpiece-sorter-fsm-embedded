#pragma once
#include "BaseStateStatus.h"

class StatusEstop : BaseStateStatus {
public:
    void estop_ok() override;
};

