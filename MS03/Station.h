// Name: Pattarawan Saravaneeyawong
// Seneca Student ID: 130618234
// Seneca email: psaravaneeyawong@myseneca.ca
// Date of completion: 20 Juy 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream> 
#include <string>
#include "Utilities.h"

namespace seneca {
	class Station {
		size_t m_id;
		std::string m_name;
		std::string m_desc;
		size_t m_serialNum;

		//Amount of items in stock
		size_t m_quantity;


		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string theStr);

		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();

		void display(std::ostream& os, bool full) const;
	};
}



#endif // !SENECA_STATION_H
