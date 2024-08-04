#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        // check if the file parameter is empty or not ---> empty: throws an exception
        if (file.empty()) {
            throw string("ERROR:File does not exist.");
        }
        //open the file ---> the file cannot be opened : throws an exception
        ifstream filename(file);
        if (!filename)
            throw string("Unable to open [") + file + "] file.";

        try {
            string record;
            while (!filename.eof()) {
                getline(filename, record);
                string workstation = record.substr(0, record.find('|'));
                string nextWorkstation = record.erase(0, workstation.size() + 1);
                auto it = find_if(stations.begin(), stations.end(), [=](Workstation* station) {
                    return workstation == station->getItemName();
                    });
                m_activeLine.push_back(*it);
                //if the next workstation is not empty --> sets it as the next station of the current workstation.
                if (nextWorkstation != "") {
                    auto it_new = find_if(stations.begin(), stations.end(), [=](Workstation* station) {
                        return nextWorkstation == station->getItemName();
                        });
                    m_activeLine.back()->setNextStation(*it_new);
                }
                //no next workstation ---> set to nullpte
                else {
                    m_activeLine.back()->setNextStation(nullptr);
                }
            }
            //searches for the first workstation and sets it as m_firstStation
            for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workStation1) {
                auto preStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workStation2) {
                    return workStation1 == workStation2->getNextStation();
                    });
                if (preStation == m_activeLine.end()) {
                    m_firstStation = workStation1;
                }
                });

            // sets the number of pending customer orders to the quantity of orders in the g_pending
            m_cntCustomerOrder = g_pending.size();
        }
        catch (...) {
            throw "Error!!!";
        }
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> orderedStations;
        orderedStations.push_back(m_firstStation);
        Workstation* currentStation = m_firstStation;
        while (currentStation->getNextStation()) {
            currentStation = currentStation->getNextStation();
            orderedStations.push_back(currentStation);
        }
        m_activeLine = orderedStations;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t cnt = 0; // track the number of iterations 
        cnt++;
        os << "Line Manager Iteration: " << cnt << std::endl;
        // checks if there are pending orders to be processed
        if (g_pending.size()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        //uses a for loop to iterate through each workstation --> calls the fill
        for (Workstation* temp : m_activeLine) {
            temp->fill(os);
        }
        //uses another for loop to iterate through each workstation --> move order
        for (Workstation* temp : m_activeLine) {
            temp->attemptToMoveOrder();
        }
        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }

    void LineManager::display(std::ostream& os) const {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* workStation) {
            workStation->display(os);
            });
    }
}