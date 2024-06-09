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
#include "Restaurant.h"

using namespace std;

namespace seneca {
	Restaurant::Restaurant() : m_reservations{ nullptr }, m_reserveNum{0}
	{
	}

	Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_reserveNum{cnt}
	{
		m_reservations = new Reservation* [m_reserveNum];

		for (size_t i = 0; i < m_reserveNum; ++i) {
			m_reservations[i] = new Reservation(*reservations[i]);
		}
	}


	Restaurant::Restaurant(const Restaurant& other) : m_reserveNum{other.m_reserveNum}
	{
		m_reservations = new Reservation*[m_reserveNum];

		for (size_t i = 0; i < m_reserveNum; i++) {
			m_reservations[i] = new Reservation(*other.m_reservations[i]);
		}

	}

	Restaurant& Restaurant::operator=(const Restaurant& other)
	{
		if (this != &other) {
			for (size_t i = 0; i < m_reserveNum; ++i) {
				delete m_reservations[i];
			}
			delete[] m_reservations;

			m_reserveNum = other.m_reserveNum;
			m_reservations = new Reservation*[m_reserveNum];

			for (size_t i = 0; i < m_reserveNum; ++i) {
				m_reservations[i] = new Reservation(*other.m_reservations[i]);
			}
		}
		return *this;
	}

	Restaurant::Restaurant(Restaurant&& other) noexcept
	{
		m_reserveNum = other.m_reserveNum;
		m_reservations = other.m_reservations;

		other.m_reservations = nullptr;
		other.m_reserveNum = 0;
	}

	Restaurant& Restaurant::operator=(Restaurant&& other) noexcept
	{
		if (this != &other) {
			for (size_t i = 0; i < m_reserveNum; ++i) {
				delete m_reservations[i];
			}
			delete[] m_reservations;

			m_reservations = other.m_reservations;
			m_reserveNum = other.m_reserveNum;

			other.m_reservations = nullptr;
			other.m_reserveNum = 0;
		}
		return *this;
	}



	Restaurant::~Restaurant()
	{
		delete[] m_reservations;
	}

	size_t Restaurant::size() const
	{
		return m_reserveNum;
	}

	std::ostream& operator<<(std::ostream& os, const Restaurant& res)
	{
		static size_t cnt = 0;
		++cnt;

		os << "--------------------------" << std::endl
			<< "Fancy Restaurant (" << cnt << ")" << std::endl
			<< "--------------------------" << std::endl;
		if (res.size() == 0)
		{
			os << "The object is empty!" << std::endl;
		}
		else {
			for (size_t i = 0; i < res.m_reserveNum; i++)
			{
				os << *res.m_reservations[i];
			}
		}
		os << "--------------------------" << std::endl;

		return os;

	}

}