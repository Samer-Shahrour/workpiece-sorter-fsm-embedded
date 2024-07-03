#pragma once
#include "BaseStateBegin.h"

class EstopBegin : public BaseStateBegin {

public:
    void estop_ok() override;
};