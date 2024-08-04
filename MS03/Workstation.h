#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>
#include <iostream>

#include "CustomerOrder.h"
#include"Station.h"

namespace seneca {
	//Have CustomerOrder first station
	extern std::deque<CustomerOrder> g_pending;

	//Have CustomerOrder that is REMOVED from LAST STATION + FILLED
	extern std::deque<CustomerOrder> g_completed;


	//Incomplete customer order cause no Items in stock
	//Order must be remove from the last station
	extern std::deque<CustomerOrder> g_incomplete;
	 
	class Workstation : public Station{
		//Orders placed to receive service
		std::deque<CustomerOrder> m_orders;

		//NO THE NEXT STATION!!!
		Workstation* m_pNextStation{};

	public:
		//Pass agrument to Station
		Workstation(const std::string& station);
		//Cannot be COPY
		Workstation(const Workstation& other) = delete;
		Workstation& operator=(const Workstation& other) = delete;
		//Cannot be Move
		Workstation(Workstation&& other) noexcept = delete;
		Workstation& operator=(Workstation& other) noexcept = delete;
		~Workstation();


		//Check if there is a CustomerOrder then fillIt
		void fill(std::ostream& os);

		//Not Done -- TRY
		bool attemptToMoveOrder();

		//Stores the address of station to the to m_pNextSTation
		//Default to nullptr
		void setNextStation(Workstation* station = nullptr);

		Workstation* getNextStation() const;
		
		//Inserts name of the item --> current object into os stream
		void display(std::ostream& os) const;

		//Push back the order from New Order
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}





#endif // SENECA_WORKSTATION_H
