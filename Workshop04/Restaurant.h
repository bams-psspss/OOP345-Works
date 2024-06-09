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
#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include <iostream>
#include "Reservation.h"

namespace seneca {
	class Restaurant
	{
		size_t m_reserveNum{};
		Reservation** m_reservations{};

	public:
		//Rule of FIVE
	
		//Default Constructor
		Restaurant();
		//Agrumemt Constructor
		Restaurant (const Reservation* reservations[], size_t cnt);

		//Copy Constructor
		Restaurant (const Restaurant& other);
		//Copy Assignment Cponstructor
		Restaurant& operator=(const Restaurant& other);

		//Move Constructor
		Restaurant(Restaurant&& other) noexcept;
		//Move Assignment operator
		Restaurant& operator= (Restaurant&& other) noexcept;

		//Destructor
		~Restaurant();

		size_t size() const;

		friend std::ostream& operator<<(std::ostream& os, const Restaurant& res);

	};
}

#endif // !SENECA_RESTAURANT_H


