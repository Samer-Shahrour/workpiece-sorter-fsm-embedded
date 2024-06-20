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
		bool isTimerRunning;

        uint64_t remainig_min_time;
        int connectionID_FSM;
		int generateId(void);

	public:
		timer_t min_time;
		timer_t max_time;
		bool still_on_belt;
		uint64_t remainig_max_time;
		Workpiece(int connectionID_FSMs);
		~Workpiece();
		int getId();
		bool minTimerOk;

        void deleteMinTimer();
        void deleteMaxTimer();

        void getRemainingMinTime();
        void getRemainingMaxTime();
        void restartMinTimer(uint64_t extraTimeInMS);
        void restartMaxTimer(uint64_t extraTimeInMS);

        void startMinTimer(int time);
        void startMaxTimer(int time);

        void deleteAndRestartMinTime(uint64_t extraTimeInMS);
        void deleteAndRestartMaxTime(uint64_t extraTimeInMS);
		WorkpieceType getType();
		void setType(WorkpieceType newType);
};
