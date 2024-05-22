#include "../../header/logik/Workpiece.h"

Workpiece::Workpiece() {
    type = WorkpieceType::DefectiveWorkpiece;
    id = generateId();
    startTimer();
}

Workpiece::~Workpiece() {
	//TODO: destruktor wiederholen
}

int Workpiece::generateId(void){
	static int idGenerator = 1;
	return idGenerator++;
}

int Workpiece::getId(){
    return id;
}

WorkpieceType Workpiece::getType(){
    return type;
}

void Workpiece::setType(WorkpieceType newType) {
    type = newType;
}

void Workpiece::startTimer() {
    startTime = std::chrono::steady_clock::now();
    isTimerRunning = true;
}

void Workpiece::stopTimer() {
    stopTime = std::chrono::steady_clock::now();
    isTimerRunning = false;
    elapsedDuration = stopTime - startTime;
}

void Workpiece::resumeTimer() {
    if (!isTimerRunning) {
        startTime = std::chrono::steady_clock::now() - elapsedDuration;
        isTimerRunning = true;
    }
}

long long Workpiece::getTimer(){
    if (isTimerRunning) {
        auto currentTime = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    }
    else {
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsedDuration).count();
    }
}
