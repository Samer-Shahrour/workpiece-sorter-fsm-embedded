#include "../../header/logik/Workpiece.h"
#include "../../header/myTimer.h"
#include "../../header/PulseCodes.h"
#include <iostream>

int static idGenerator = 0;

Workpiece::Workpiece(int connectionID_FSMs) {
    type = WorkpieceType::DefectiveWorkpiece;
    wp_id = generateId();
    connectionID_FSM = connectionID_FSMs;
    still_on_belt = true;
}

Workpiece::~Workpiece() {
}

int Workpiece::generateId(void){
	return idGenerator++;
}

void resetGenerater(void){
    idGenerator = 0;
}

int Workpiece::getId(){
    return wp_id;
}

WorkpieceType Workpiece::getType(){
    return type;
}

void Workpiece::setType(WorkpieceType newType) {
    type = newType;
}

void Workpiece::deleteMaxTimer() {
    printf("Max Timer deleted for WP-ID: %d\n", wp_id);
    myDeleteTimer(max_time);
}

void Workpiece::getRemainingMaxTime() {
    remainig_max_time = getRemainingTimeInMS(max_time);
}


void Workpiece::restartMaxTimer(uint64_t extraTimeInMS){
    if(remainig_max_time){
        myStartTimer(&max_time, connectionID_FSM, PULSE_TIME_OUT_WP_MAX, wp_id, false, (remainig_max_time+extraTimeInMS));
        std::cout << "Max-Timer REstarted RemainingTime = " << getRemainingTimeInMS(max_time) << " mit ID: " << wp_id << std::endl;
        remainig_max_time = 0;
    }
}

void Workpiece::startMaxTimer(int time){
    myStartTimer(&max_time, connectionID_FSM, PULSE_TIME_OUT_WP_MAX, wp_id, false, time);
    std::cout << "Max-Timer started RemainingTime = " << getRemainingTimeInMS(max_time) << " mit ID: " << wp_id << std::endl;
}


void Workpiece::deleteAndRestartMaxTime(uint64_t extraTimeInMS){
	/*
    uint64_t rem_time = getRemainingTimeInMS(max_time);
    myDeleteTimer(max_time);
    uint64_t new_time = rem_time + extraTimeInMS;
    max_time = myStartTimer(connectionID_FSM, PULSE_TIME_OUT_WP_MAX, wp_id, false, new_time);
    */
}
