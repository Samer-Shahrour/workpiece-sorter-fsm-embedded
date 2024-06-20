#pragma once
#include <time.h>
#include <chrono>

enum class WorkpieceType {
    FlatWorkpiece,
    MetalWorkpiece,
    DefectiveWorkpiece
};


void resetGenerater(void);

class Workpiece {
	private:
		int wp_id;
		WorkpieceType type;
        int connectionID_FSM;
		int generateId(void);

	public:
		timer_t max_time;
        uint64_t remainig_max_time;
        bool still_on_belt;
        long long minTimeStamp;

        WorkpieceType getType();
        void setType(WorkpieceType newType);
		Workpiece(int connectionID_FSMs);
		~Workpiece();
		int getId();
        void deleteMaxTimer();
        void getRemainingMaxTime();
        void restartMaxTimer(uint64_t extraTimeInMS);
        void startMaxTimer(int time);
        void deleteAndRestartMaxTime(uint64_t extraTimeInMS);

};
