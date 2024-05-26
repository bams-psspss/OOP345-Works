/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		26 May 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <chrono>
#include <thread>

#include "TimedTask.h"

using namespace std;

namespace seneca {
	TimedTask::TimedTask() : m_numRecStored{ 0 } {
	}
	void TimedTask::startClock() {
		m_startTime = std::chrono::steady_clock::now();
	}

	void TimedTask::stopClock() {
		m_endTime = std::chrono::steady_clock::now();
	}

	void TimedTask::addTask(const char* taskName) {
		if (m_numRecStored < MAX_TASK) {
			m_tasks[m_numRecStored].taskName = taskName;
			m_tasks[m_numRecStored].unitOfTime = "nanoseconds";
			m_tasks[m_numRecStored].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);

			m_numRecStored++;
		}
	}

	std::ostream& operator<<(std::ostream& ostr, const TimedTask& timeT) {
		ostr << "--------------------------\n";
		ostr << "Execution Times:\n";
		ostr << "--------------------------\n";

		for (int i = 0; i < timeT.m_numRecStored; i++) {
			ostr << std::left << std::setw(21) << timeT.m_tasks[i].taskName;
			ostr << std::right << std::setw(13) << timeT.m_tasks[i].duration.count();
			ostr << " " << timeT.m_tasks[i].unitOfTime << '\n';
		}

		ostr << "--------------------------\n";
		return ostr;

	}
}
