
#include "../../header/FSMs/FSMThread.h"
#include "../../header/FSMs/BeginFSM/ContextBegin.h"
#include "../../header/FSMs/ErrorFSM/ContextError.h"
#include "../../header/FSMs/StopFSM/ContextStop.h"
#include "../../header/FSMs/E_Stop/ContextEstop.h"
#include "../../header/FSMs/hightMeasurmentFSM/ContextHM.h"
#include "../../header/FSMs/SwitchFSM/ContextSwitch.h"
#include "../../header/FSMs/EndFSM/ContextEnd.h"
#include "../../header/FSMs/M2_Status/ContextStatus.h"
#include "../../header/variables.h"
#include "../../header/Hal/Actuators.h"


void FSM_Thread(int channelID_FSM, int connectionID_FSM, int connectionID_Dispatcher){
    ThreadCtl(_NTO_TCTL_IO, 0);
    bool inOperation = false;

    ContextData *data = new ContextData();
    data->isSwitch = checkSwitch();
    ContextModes modesFsm   (connectionID_FSM, connectionID_Dispatcher, data);
    ContextEstop estopFsm   (connectionID_Dispatcher, connectionID_FSM,  data);
    ContextError errorFsm   (connectionID_FSM, connectionID_Dispatcher, data);
    ContextBegin beginFsm   (connectionID_FSM, connectionID_Dispatcher, data);
    ContextStop  stopFsm    (connectionID_FSM, connectionID_Dispatcher, data);
    ContextHM    HMFsm      (connectionID_FSM, connectionID_Dispatcher, data);
    ContextSwitch switchFsm (connectionID_FSM, connectionID_Dispatcher, data);
    ContextEnd   endFsm     (connectionID_FSM, connectionID_Dispatcher, data);
    ContextStatus statusFsm (connectionID_Dispatcher, data);
    _pulse msg;
    bool receiveRunning = true;
    while(receiveRunning){
        if (myReceivePulse(channelID_FSM, &msg) > 0) {
            continue;
        }
        switch(msg.code){
            case PULSE_STOP_THREAD:
                printf("Dispatcher Thread kill code received!\n");
                receiveRunning = false;
                break;
            case PULSE_CALIBRATION_OPERATION:
                if(msg.value.sival_int){
                    inOperation = false;
                } else{
                    inOperation = true;
                }
                break;
            case PULSE_LOW_HIGH_MACHINE2:
                switch (msg.value.sival_int){
                    case E_STOP:
                        estopFsm.m2_estop_released();
                        break;
                    case BUTTON_START:
                        modesFsm.m1_start_pressed();
                        if(inOperation){
                            statusFsm.start_pressed();
                            stopFsm.start_pressed();
                        }
                        break;
                    case BUTTON_RESET:
                        errorFsm.reset_pressed();
                        estopFsm.m2_reset_pressed();
                        break;
                    case LBB:
                        modesFsm.lbb_free();
                        if(inOperation){
                            beginFsm.m2_lbb_free();
                        }
                        break;
                    case IS_METAL:
                        if(inOperation){
                            switchFsm.metal_detected();
                        }
                        break;
                    case LBS:
                        if(inOperation){
                            switchFsm.lbs_free();
                        }
                        break;
                    case LBC: // Wenn Rutsche wieder frei ist
                        if(inOperation){
                            switchFsm.lbc_free();
                        }
                        break;
                    case LBE:
                        if(inOperation){
                            statusFsm.lbe_free();
                            endFsm.m2_lbe_free();
                            beginFsm.m2_lbe_free();
                            stopFsm.m2_lbe_free();
                        }
                        break;
                }
                break;

            case PULSE_HIGH_LOW_MACHINE2:
                switch (msg.value.sival_int) {
                    case E_STOP:
                        estopFsm.m2_estop_pressed();
                        modesFsm.m2_estop_pressed();
                        errorFsm.m2_estop_pressed();
                        beginFsm.m2_estop_pressed();
                        stopFsm.m2_estop_pressed();
                        HMFsm.m2_estop_pressed();
                        switchFsm.m2_estop_pressed();
                        endFsm.m2_estop_pressed();
                        statusFsm.m2_estop_pressed();
                       // inOperation = false;
                        break;
                    case BUTTON_START:
                        modesFsm.m1_start_released();
                        break;
                    case BUTTON_STOP:
                        if(inOperation){
                            statusFsm.stop_pressed();
                            stopFsm.stop_pressed();
                        }
                        break;
                    case LBB:
                        modesFsm.lbb_blocked();
                        if(inOperation){
                            statusFsm.lbb_blocked();
                            beginFsm.m2_lbb_blocked();
                        }
                        break;
                    case LBS:
                        modesFsm.lbs_blocked();
                        if(inOperation){
                        	switchFsm.lbs_blocked();
                        }
                        break;
                    case LBC:
                        modesFsm.lbc_blocked();
                        if(inOperation){
                            statusFsm.lbc_blocked();
                            switchFsm.lbc_blocked();
                            beginFsm.m2_lbc_blocked();
                        }
                        break;
                    case LBE:
                        modesFsm.lbe_blocked();
                        if(inOperation){
                            endFsm.m2_lbe_blocked();
                            stopFsm.m2_lbe_blocked();
                        }
                        break;
                }
                break;

            case PULSE_HIGH_LOW_MACHINE1:
                switch (msg.value.sival_int) {
                    case E_STOP:
                        estopFsm.m1_estop_pressed();
                        modesFsm.m1_estop_pressed();
                        errorFsm.m1_estop_pressed();
                        beginFsm.m1_estop_pressed();
                        stopFsm.m1_estop_pressed();
                        HMFsm.m1_estop_pressed();
                        switchFsm.m1_estop_pressed();
                        endFsm.m1_estop_pressed();
                        statusFsm.m1_estop_pressed();
                        inOperation = false;
                        break;
                }
                break;
            case PULSE_LOW_HIGH_MACHINE1:
                switch (msg.value.sival_int) {
                    case E_STOP:
                        estopFsm.m1_estop_released();
                        break;
                    case BUTTON_RESET:
                        estopFsm.m1_reset_pressed();
                        break;
                }
                break;

            case PULSE_TIME_START:
                modesFsm.time_out_start();
                break;
            case PULSE_ESTOP_OK:
                statusFsm.estop_ok();
                modesFsm.estop_ok();
                errorFsm.estop_ok();
                beginFsm.estop_ok();
                stopFsm.estop_ok();
                HMFsm.estop_ok();
                switchFsm.estop_ok();
                endFsm.estop_ok();
                break;

            case PULSE_TICK_CALIBRATION:
                modesFsm.incrementSection();
                break;

            case PULSE_HIGHT:
                if(inOperation){
                    HMFsm.hight_changed(msg.value.sival_int);
                }
                modesFsm.hight_changed();
                break;
            case PULSE_ERROR:
                statusFsm.error();
                errorFsm.error();
                beginFsm.error();
                stopFsm.error();
                HMFsm.error();
                switchFsm.error();
                endFsm.error();
                break;

            case PULSE_ERROR_OK:
                statusFsm.error_ok();
                beginFsm.error_ok();
                stopFsm.error_ok();
                HMFsm.error_ok();
                switchFsm.error_ok();
                endFsm.error_ok();
                break;

            case PULSE_TIME_OUT_WP_MAX: // Falls Max time kommt und wp noch nicht da ist
                if(inOperation){
                    stopFsm.error();
                    beginFsm.error();
                    HMFsm.error();
                    errorFsm.error();
                    endFsm.error();
                    statusFsm.error();
                }
                printf("FSM THREAD: Max Time id:(%d)\n", msg.value.sival_int);
                break;
            case PULSE_SEND_WP_TO_M2: // WP Type von m1 reciven
                if(inOperation){
                    beginFsm.info_received();
                    switch (msg.value.sival_int) {
                        case WP_FLAT:
                            data->queue[0].type_received_from_m1 = WorkpieceType::FlatWorkpiece;
                            break;
                        case WP_METAL:
                            data->queue[0].type_received_from_m1 = WorkpieceType::MetalWorkpiece;
                            break;
                        case WP_UNDEFIND:
                            data->queue[0].type_received_from_m1 = WorkpieceType::DefectiveWorkpiece;
                            break;
                    }
                }
                break;
        }
    }
    printf("FSM Thread Done!\n");
}
