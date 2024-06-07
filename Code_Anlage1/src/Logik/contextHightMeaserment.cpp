#include <thread>
#include <iostream>
#include <sys/neutrino.h>

#include "../../header/ChannelUtils.h"
#include "../../header/PulseCodes.h"
#include "../../header/Logik/contextHightMeaserment.h"


void hightMeasurementThread(int channelID_FSM_Hight_Measurement, int connectionID_Encoder, int connectionID_Dispatcher){
    ThreadCtl(_NTO_TCTL_IO, 0);

    /*
    TSCADC tscadc;
    ADC *adc = new ADC(tscadc);
    adc->registerAdcISR(connectionID_Encoder, PULSE_HIGHT);

    _pulse msg;
    bool receiveRunning = true;
    while(receiveRunning){
        int recvid = myReceivePulse(channelID_FSM_Hight_Measurement, &msg);
        if (recvid > 0) {
            continue;
        }
        switch(msg.code){
            case PULSE_STOP_THREAD:
                printf("Hight Measurement Thread kill code received!\n");
                receiveRunning = false;
                break;

            case PULSE_HIGHT:
                printf("Hight received! _ %d _\n", msg.value.sival_int);
                break;
        }
    }*/
    printf("FSM Thread Done!\n");
}


ContextHightMeasurement::ContextHightMeasurement(){
//    state = new
}
ContextHightMeasurement::~ContextHightMeasurement(){
    delete state;
}

void ContextHightMeasurement::showState(){

}
void ContextHightMeasurement::beltHight(){

}
void ContextHightMeasurement::sideHight(){

}
void ContextHightMeasurement::highWPHight(){

}
void ContextHightMeasurement::flatWPHight(){

}
void ContextHightMeasurement::holeHight(){

}
void ContextHightMeasurement::otherHight(){

}
