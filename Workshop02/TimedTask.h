/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		26 May 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
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
