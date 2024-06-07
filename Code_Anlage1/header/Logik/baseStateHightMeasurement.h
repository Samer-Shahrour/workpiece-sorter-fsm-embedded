#pragma once

#include "../../header/Logik/ContextData.h"
#include <iostream>
using namespace std;

class BaseStateHightMeasurement {
protected:
    //ContextActions *data;
public:
    virtual ~BaseStateHightMeasurement(){};
    //void setActions(ContextData *actions){this->data = actions;};
    virtual void showState(){};

    virtual void beltHight(){};
    virtual void sideHight(){};
    virtual void highWPHight(){};
    virtual void flatWPHight(){};
    virtual void holeHight(){};
    virtual void otherHight(){};

};
