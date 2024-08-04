#include <iostream>
#include <deque>
#include "Workstation.h"

 
namespace seneca {
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const std::string& str) : Station(str) {}//passes it to the Station base class.

	Workstation::~Workstation() {
		//no need to deallocation
	}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool result = false;

		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation != nullptr) {
					*m_pNextStation += (std::move(m_orders.front()));
				}
				else {
					m_orders.front().isOrderFilled() ? g_completed.push_back(std::move(m_orders.front())) :
						g_incomplete.push_back(std::move(m_orders.front()));

				}
				m_orders.pop_front();
				result = true;
			}
		}
		return result;
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
		os << endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {

		m_orders.push_back(move(newOrder));
		return *this;
	}

}