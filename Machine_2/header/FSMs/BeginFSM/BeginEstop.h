#pragma once
#include "BaseStateBegin.h"

class BeginEstop : public BaseStateBegin {
public:
    void estop_ok() override;
};
