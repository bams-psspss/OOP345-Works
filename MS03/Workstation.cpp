#include <iostream>
#include <deque>
#include "Workstation.h"

 
namespace seneca {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;


	Workstation::Workstation(const std::string& station) : Station(station),
		m_orders(), m_pNextStation(nullptr)
	{
	}

	void Workstation::fill(std::ostream& os)
	{
		if(!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool moved = false;

		// Check if the Orders is Empty or Not
		if (!m_orders.empty()) {
			// Check if the order is filled or cannot be filled (not enough inventory)
			if (m_orders.front().isOrderFilled() || (getQuantity() < 1)) {
				if (m_pNextStation == nullptr) {
					// Order is filled --> put it in g_completed
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(std::move(m_orders.front()));
					}
					// Order is not filled --> put it in g_incomplete
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
					}
				}
				else {
					// Move the order to the next station
					*m_pNextStation += std::move(m_orders.front());
				}
				// Remove the order from the current station's queue
				m_orders.pop_front();
				moved = true;
			}
		}
		return moved;
	}
	

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation != nullptr) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << '\n';
		}
		else {
			os << getItemName() << " --> End of Line\n";
		}

	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}