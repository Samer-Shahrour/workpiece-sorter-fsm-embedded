#include <sys/neutrino.h>
#include "../header/logger.h"
#include "../header/Hal/Sensors.h"
#include "../header/Hal/Actuators.h"
#include "../header/PulseCodes.h"
#include <stdio.h>

#define LOG_ACTIONS false

void log_actions(_pulse msg){
	switch(msg.code){
		case PULSE_FROM_FSM_TO_HAL:
	                switch (msg.value.sival_int) {
	                        case MOVE_RIGHT:
	                            printf("Logger: move_right() \n");
	                        break;
	                        case MOVE_LEFT:
	                            printf("Logger: move_left() \n");
	                        break;
	                        case STOP:
	                            printf("Logger: stop_motor() \n");
	                        break;
	                        case BLOCK:
	                            printf("Logger: motor_block() \n");
	                        break;
	                        case UNBLOCK:
	                            printf("Logger: motor_unblock() \n");
	                        break;
	                        case MOTOR_FAST:
	                            printf("Logger: move_motor_fast()\n");
	                        break;
	                        case MOTOR_SLOW:
	                            printf("Logger: move_motor_slow()\n");
	                        break;
	                        case LED_START + LIGHT_ON:
	                            printf("Logger: led_start_on() \n");
	                        break;
	                        case LED_RESET + LIGHT_ON:
	                            printf("Logger: led_reset_on() \n");
	                        break;
	                        case LED_Q1 + LIGHT_ON:
	                            printf("Logger: led_Q1_on()\n");
	                        break;
	                        case LED_Q2 + LIGHT_ON:
	                            printf("Logger: led_Q2_on()\n");
	                        break;
	                        case LED_START + LIGHT_OFF:
	                            printf("Logger: led_start_off()\n");
	                        break;
	                        case LED_RESET + LIGHT_OFF:
	                            printf("Logger: led_reset_off()\n");
	                        break;
	                        case LED_Q2 + LIGHT_OFF:
	                            printf("Logger: led_q2_off()\n");
	                        break;
	                        case LED_Q1 + LIGHT_OFF:
	                            printf("Logger: led_q1_off()\n");
	                        break;
	                        case RED + LIGHT_ON:
	                            printf("Logger: lamp_red_on()\n");
	                        break;
	                        case YELLOW + LIGHT_ON:
	                            printf("Logger: lamp_yellow_on()\n");
	                        break;
	                        case GREEN + LIGHT_ON:
	                            printf("Logger: lamp_green_on()\n");
	                        break;
	                        case RED + LIGHT_OFF:
	                            printf("Logger: lamp_red_off()\n");
	                        break;
	                        case YELLOW + LIGHT_OFF:
	                            printf("Logger: lamp_yellow_off()\n");
	                        break;
	                        case GREEN + LIGHT_OFF:
	                            printf("Logger: lamp_green_off()\n");
	                        break;
	                        case SORT_OUT:
	                            printf("Logger: sort_out() \n");
	                        break;
	                        case LET_THROUGH:
	                            printf("Logger: let_through() \n");
	                        break;
	                    }
	                break;
	}

}

void loggerThread(int channelID_logger){
    ThreadCtl(_NTO_TCTL_IO, 0);
    _pulse msg;
    bool receiveRunning = true;
    while(receiveRunning){
        if(MsgReceivePulse(channelID_logger, &msg, sizeof(_pulse), nullptr) < 0) {
            continue;
        }
        switch(msg.code) {
            case PULSE_HIGHT:
                switch (msg.value.sival_int) {
                    case 1:
                        printf("Logger: Flat detected\n");
                        break;
                    case 2:
                        printf("Logger: NOT Flat detected\n");
                        break;
                }
                break;
            case PULSE_HIGH_LOW_MACHINE1:
                switch (msg.value.sival_int) {
                    case LBB:
                        printf("Logger: M1_LBB_BLOCKED\n");
                        break;
                    case LBS:
                        printf("Logger: M1_LBS_BLOCKED\n");
                        break;
                    case LBC:
                        printf("Logger: M1_LBC_BLOCKED\n");
                        break;
                    case LBE:
                        printf("Logger: M1_LBE_BLOCKED\n");
                        break;
                    case BUTTON_START:
                        printf("Logger: M1_START_RELEASED\n");
                        break;
                    case BUTTON_RESET:
                        printf("Logger:  M1_RESET_RELEASED\n");
                        break;
                    case BUTTON_STOP:
                        printf("Logger:  M1_STOP_PRESSED\n");
                        break;
                    case E_STOP:
                        printf("Logger:  M1_ESTOP_PRESSED\n");
                        break;
                }
                break;
            case PULSE_LOW_HIGH_MACHINE1:
                switch (msg.value.sival_int) {
                    case LBB:
                        printf("Logger: M1_LBB_FREE \n");
                        break;
                    case LBS:
                        printf("Logger: M1_LBS_FREE \n");
                        break;
                    case LBC:
                        printf("Logger: M1_LBC_FREE \n");
                        break;
                    case LBE:
                        printf("Logger: M1_LBE_FREE \n");
                        break;
                    case BUTTON_START:
                        printf("Logger: M1_START_PRESSED\n");
                        break;
                    case BUTTON_RESET:
                        printf("Logger: M1_RESET_PRESSED \n");
                        break;
                    case BUTTON_STOP:
                        printf("Logger: M1_STOP_RELEASED \n");
                        break;
                    case E_STOP:
                        printf("Logger: M1_ESTOP_RELEASED \n");
                        break;
                    case IS_METAL:
                        printf("Logger: M1_METAL_DETECTED \n");
                        break;
                }
                break;
            case PULSE_HIGH_LOW_MACHINE2:
                switch (msg.value.sival_int) {
                    case LBB:
                        printf("Logger: M2_LBB_BLOCKED\n");
                        break;
                    case LBS:
                        printf("Logger: M2_LBS_BLOCKED\n");
                        break;
                    case LBC:
                        printf("Logger: M2_LBC_BLOCKED\n");
                        break;
                    case LBE:
                        printf("Logger: M2_LBE_BLOCKED\n");
                        break;
                    case BUTTON_START:
                        printf("Logger: M2_START_RELEASED\n");
                        break;
                    case BUTTON_RESET:
                        printf("Logger: M2_RESET_RELEASED\n");
                        break;
                    case BUTTON_STOP:
                        printf("Logger: M2_STOP_PRESSED\n");
                        break;
                    case E_STOP:
                        printf("Logger: M2_ESTOP_PRESSED\n");
                        break;
                }
                break;
            case PULSE_LOW_HIGH_MACHINE2:
                switch (msg.value.sival_int) {
                    case LBB:
                        printf("Logger: M2_LBB_FREE \n");
                        break;
                    case LBS:
                        printf("Logger: M2_LBS_FREE \n");
                        break;
                    case LBC:
                        printf("Logger: M2_LBC_FREE \n");
                        break;
                    case LBE:
                        printf("Logger: M2_LBE_FREE \n");
                        break;
                    case BUTTON_START:
                        printf("Logger: M2_START_PRESSED\n");
                        break;
                    case BUTTON_RESET:
                        printf("Logger: M2_RESET_PRESSED \n");
                        break;
                    case BUTTON_STOP:
                        printf("Logger: M2_STOP_RELEASED \n");
                        break;
                    case E_STOP:
                        printf("Logger: M2_ESTOP_RELEASED \n");
                        break;
                    case IS_METAL:
                        printf("Logger: M2_METAL_DETECTED \n");
                        break;
                }
                break;

            case PULSE_FLASH_ON:
                printf("Logger: Green Lamp Flash 0,5Hz \n");
                break;

            case PULSE_FLASH_OFF:
                printf("Logger: Green Lamp Flash Stops \n");
                break;

            case PULSE_CALIBRATION_OPERATION:
                switch(msg.value.sival_int){
                    case 1:
                        printf("Logger: Calibration-Mode\n");
                        break;
                    case 0:
                        printf("Logger: Operation-Mode\n");
                        break;
                }
                break;
            case PULSE_ESTOP_OK:
                printf("Logger: ESTOP_OK\n");
                break;
            case PULSE_ERROR:
            printf("Logger: Error \n");
            break;
            case PULSE_ERROR_OK:
                printf("Logger: Error_OK \n");
                break;
            case PULSE_TIME_OUT_WP_MIN:
                printf("Logger: TIME_MIN_OUT \n");
                break;
            case PULSE_TIME_OUT_WP_MAX:
                printf("Logger: TIME_MAX_OUT \n");
                break;
        }
        if(LOG_ACTIONS){
        	log_actions(msg);
        }
    }
}
