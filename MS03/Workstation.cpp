#include <iostream>
#include <deque>
#include "Workstation.h"

 
namespace seneca {
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string& str) :Station(str) {}

    Workstation::~Workstation(){
     delete m_pNextStation;
    }

    void Workstation::fill(std::ostream& os) {
        //checks if there are any orders in the current workstation.
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        //checks if there are any orders in the current workstation.
        if (!m_orders.empty()) {

            //checks if the items in the current order are already filled
            if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0) {

                // check if there is a next workstation
                if (m_pNextStation != nullptr) {
                    *m_pNextStation += std::move(m_orders.front());  //move the current order to the next workstation
                }

                //no next workstation
                else {

                    //is the current order completely filled?
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));  //yes
                    }
                    else {
                        g_incomplete.push_back(std::move(m_orders.front())); //no
                    }
                }
                m_orders.pop_front();
                return true;
            }
        }
        return false;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation == nullptr) {
            os << "End of Line";
        }
        else {
            os << m_pNextStation->getItemName();
        }
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

}
