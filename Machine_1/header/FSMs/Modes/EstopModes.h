#pragma once
#include "BaseStateModes.h"

class EstopModes : public BaseStateModes{
public:
    void estop_ok() override;
};
