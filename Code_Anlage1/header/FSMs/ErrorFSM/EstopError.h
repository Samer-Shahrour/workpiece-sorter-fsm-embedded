#pragma once
#include "BaseStateError.h"

class EstopError : public BaseStateError{
    public:
    void estop_ok() override;
};