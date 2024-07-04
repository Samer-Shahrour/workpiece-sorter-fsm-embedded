#pragma once
#include "BaseStateEnd.h"

class EndEstop : public BaseStateEnd {
public:
    void estop_ok() override;
};
