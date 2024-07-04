#pragma once
#include <sys/neutrino.h>


#define PULSE_STOP_THREAD                 	_PULSE_CODE_MINAVAIL + 1
#define PULSE_INTRRUPT                 	   	_PULSE_CODE_MINAVAIL + 2
#define PULSE_GPIO                    	    _PULSE_CODE_MINAVAIL + 3

#define PULSE_LOW_HIGH_MACHINE1           	_PULSE_CODE_MINAVAIL + 5
#define PULSE_HIGH_LOW_MACHINE1           	_PULSE_CODE_MINAVAIL + 6
#define PULSE_LOW_HIGH_MACHINE2        		_PULSE_CODE_MINAVAIL + 7
#define PULSE_HIGH_LOW_MACHINE2           	_PULSE_CODE_MINAVAIL + 8

#define PULSE_HIGHT                      	_PULSE_CODE_MINAVAIL + 9

#define PULSE_FROM_FSM_TO_HAL           	_PULSE_CODE_MINAVAIL + 10

#define PULSE_CALIBRATION_OPERATION         _PULSE_CODE_MINAVAIL + 11

//Timer Codes
#define PULSE_TIME_START                    _PULSE_CODE_MINAVAIL + 12
#define PULSE_TIME_OUT_WP_MIN               _PULSE_CODE_MINAVAIL + 13
#define PULSE_TIME_OUT_WP_MAX               _PULSE_CODE_MINAVAIL + 14

#define PULSE_TICK_CALIBRATION              _PULSE_CODE_MINAVAIL + 15
#define PULSE_TIME_OUT_BEGIN                _PULSE_CODE_MINAVAIL + 16
#define PULSE_TIME_SWITCH_OUT               _PULSE_CODE_MINAVAIL + 17

// PULSE FLASH
#define PULSE_TIME_OUT_FLASH    			_PULSE_CODE_MINAVAIL + 18
#define PULSE_FLASH_ON						_PULSE_CODE_MINAVAIL + 19
#define PULSE_FLASH_OFF						_PULSE_CODE_MINAVAIL + 20


// ESTOP
#define PULSE_ESTOP_OK                      _PULSE_CODE_MINAVAIL + 21
#define PULSE_ERROR_OK                      _PULSE_CODE_MINAVAIL + 22
#define PULSE_ERROR                         _PULSE_CODE_MINAVAIL + 23

#define PULSE_CONNECTION_CHECK              _PULSE_CODE_MINAVAIL + 24
#define PULSE_CONNECTION_LOST               _PULSE_CODE_MINAVAIL + 25

#define PULSE_M2_STATUS                     _PULSE_CODE_MINAVAIL + 26
#define PULSE_SEND_WP_TO_M2                 _PULSE_CODE_MINAVAIL + 27