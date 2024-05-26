#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <cstring>
#include <chrono>


namespace seneca {
	struct Task {
		std::string taskName{};
		std::string unitOfTime{};
		std::chrono::steady_clock::duration duration{};
	};
	
	class TimedTask {
		static const int MAX_TASK = 10;

		int m_numRecStored;
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_endTime;
		Task m_tasks[MAX_TASK];

	public:
		TimedTask();

		void startClock();
		void stopClock();
		void addTask(const char* taskName);

		friend std::ostream& operator<<(std::ostream& ostr, const TimedTask& tt);

	};
}

#endif // !SENECA_TIMEDTASK_H
