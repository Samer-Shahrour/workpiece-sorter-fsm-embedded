#pragma once

class EStopActions{

private:
    void sendMsg(int);
public:
    int connectionID_Dispatcher;
    void turnRed(bool);
    void turnYellow(bool);
    void startRedFLASH(void);
    void stopRedFLASH(void);
    void motorBlock(void);
    void motorUnblock(void);
    void sortOut(void);
    void letThrough(void);
    void motorStart(void);
    void motorStop(void);
};
