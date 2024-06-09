/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		08 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#pragma once
#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H
#include <iostream>
#include <string>

namespace seneca {
	class Reservation
	{
		
		std::string m_reserveId{};
		std::string m_nameReserve{};
		std::string m_email{};
		int m_partyNum{};
		int m_day{};
		int m_hour{};
		
	public:
		//Default Constructor
		Reservation();
	
		//Constructor with Agrument
		Reservation(const std::string& res);

		//Update day and hour
		void update(int day, int time);

		friend std::ostream& operator<<(std::ostream& os, const Reservation& res);


	};


}

#endif // !SENECA_RESERVATION_H
