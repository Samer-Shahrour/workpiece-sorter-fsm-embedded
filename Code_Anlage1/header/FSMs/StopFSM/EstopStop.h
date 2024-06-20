#pragma once
#include "BaseStateStop.h"

class EstopStop : public BaseStateStop{
    public:
    void estop_ok() override;
};
