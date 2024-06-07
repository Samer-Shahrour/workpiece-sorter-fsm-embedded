#pragma once

#include <chrono>

enum class WorkpieceType {
    FlatWorkpieces,
    HighWorkpiecesWithoutHole,
    HighWorkpiecesWithHoleAndMetalInsert,
    HighWorkpiecesWithHoleWithoutMetalInsert_OLD,
    HighWorkpiecesWithHoleWithoutMetalInsert_NEW,
    BinaryCodedWorkpieces,
    DefectiveWorkpiece
};

class Workpiece {
	private:
		int id;
		WorkpieceType type;
		bool isTimerRunning;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point stopTime;
		std::chrono::steady_clock::duration elapsedDuration;
		int generateId(void);

	public:
		Workpiece();
		~Workpiece();
		int getId();

		WorkpieceType getType();
		void setType(WorkpieceType newType);

		void startTimer();
		void stopTimer();
		void resumeTimer();
		long long getTimer();
};
