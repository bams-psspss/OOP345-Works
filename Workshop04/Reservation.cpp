/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		08 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include "Reservation.h"

using namespace std;

namespace seneca {
	//Constant for hour for
	const int MOR_ST = 6;
	const int MOR_ED = 9;

	const int LUN_ST = 11;
	const int LUN_ED = 15;

	const int DIN_ST = 17;
	const int DIN_ED = 21;

	//Helper function, no need prototype in class, because does not count as
	static string trim(const string& theStr) {
		//Return npos if first position is NOT spacebar
		size_t first = theStr.find_first_not_of(' ');

		size_t last = theStr.find_last_not_of(' ');

		if (first == string::npos) {
			return theStr; //First char is not space return the aggrument
		}

		return theStr.substr(first, (last - first + 1));
	}

	Reservation::Reservation() : m_reserveId{}, m_nameReserve{}, m_email{}, 
		m_partyNum{ 0 }, m_day{ 0 }, m_hour{0}
	{
	}

	Reservation::Reservation(const std::string& res)
	{
		size_t start = 0;
		size_t end = res.find(':');

		string temp = {};

		m_reserveId = trim(res.substr(start, end - start));

		start = end + 1;
		end = res.find(',', start);
		m_nameReserve = trim(res.substr(start, end - start));

		start = end + 1;
		end = res.find(',', start);
		m_email = trim(res.substr(start, end - start));

		start = end + 1;
		end = res.find(',', start);
		m_partyNum = std::stoi(trim(res.substr(start, end - start)));

		start = end + 1;
		end = res.find(',', start);
		m_day = std::stoi(trim(res.substr(start, end - start)));

		start = end + 1;
		m_hour = std::stoi(trim(res.substr(start)));

	}

	void Reservation::update(int day, int time)
	{
		m_day = day;
		m_hour = time;
	}

	std::ostream& operator<<(std::ostream& os, const Reservation& res)
	{
		string mealType{};

		if (res.m_hour >= MOR_ST && res.m_hour <= MOR_ED) {
			mealType = "Breakfast";
		}
		else if (res.m_hour >= LUN_ST && res.m_hour <= LUN_ED) {
			mealType = "Lunch";

		}else if (res.m_hour >= DIN_ST && res.m_hour <= DIN_ED) {
			mealType = "Dinner";
		}
		else {
			mealType = "Drinks";
		}



		os << "Reservation "
			<< std::setw(10) << std::right << res.m_reserveId << ": "
			<< std::setw(20) << std::right << res.m_nameReserve << " "

			<< std::setw(25) << std::left << (" <" + res.m_email + ">")
			<< mealType << " on day "
			<< res.m_day << " @ " << res.m_hour << ":00"
			<< " for " << res.m_partyNum
			<< (res.m_partyNum > 1 ? " people" : " person") << ".\n";




		return os;
	}

}
                                                                                                  