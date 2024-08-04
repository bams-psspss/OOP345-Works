#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "LineManager.h"
#include "Utilities.h"


namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream infile(file);
        if (!infile) {
            throw std::runtime_error("Failed to open file: " + file);
        }

        std::string line, currentStation, nextStation;
        while (std::getline(infile, line)) {
            std::istringstream record(line);
            std::getline(record, currentStation, '|');
            std::getline(record, nextStation);

            auto currentIt = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                return ws->getItemName() == currentStation;
                });
            
            auto nextIt = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                return ws->getItemName() == nextStation;
                });

            if (currentIt != stations.end()) {
                m_activeLine.push_back(*currentIt);
                if (nextIt != stations.end()) {
                    (*currentIt)->setNextStation(*nextIt);
                }
            }
        }

        if (!m_activeLine.empty()) {
            m_firstStation = m_activeLine.front();
            std::for_each(stations.begin(), stations.end(), [&](Workstation* ws) {
                if (std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* active) {
                    return active->getNextStation() == ws;
                    })) {
                    m_firstStation = ws;
                }
                });
        }

        m_cntCustomerOrder = g_pending.size();
    }


    void LineManager::reorderStations() {
        std::vector<Workstation*> temp;
        Workstation* ws;
        temp.push_back(m_firstStation);
        while ((ws = temp.back()->getNextStation())) {
            temp.push_back(ws);
        }
        m_activeLine = temp;
    }
    bool LineManager::run(std::ostream& os) {
        static size_t count{};
        count++;
        os << "Line Manager Iteration: " << count << std::endl;
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            ws->fill(os);
            });
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            ws->attemptToMoveOrder();
            });

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }


	void LineManager::display(std::ostream& os) const
	{
		for (auto item : m_activeLine)
			item->display(os);
	}
}