// Name: Pattarawan Saravaneeyawong
// Seneca Student ID: 130618234
// Seneca email: psaravaneeyawong@myseneca.ca
// Date of completion: 20 Juy 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <string>

#include "Station.h"


namespace seneca {

	struct Item {
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		//A pointer to an array of pointer, which the pointer in array points
		//to each STRUCT ITEM
		Item** m_lstItem{};

		//Display Purpose
		static size_t m_widthField;

	public:
		//Default Constructor
		CustomerOrder();

		//Constructor with 1 argument constructor
		CustomerOrder(const std::string& theStr);

		//Copy Constructor THROW ERROR!
		CustomerOrder(const CustomerOrder& other);
		//Assignment Operator THROW ERROR!
		CustomerOrder& operator= (const CustomerOrder& other);

		//Move Constructor
		CustomerOrder( CustomerOrder&& other) noexcept;
		//Move Assignment Operator
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;
	
		~CustomerOrder();


		bool isOrderFilled() const;
		//???? Review it again
		bool isItemFilled(const std::string& itemName) const;
		//Not sure???
		void fillItem(Station& station, std::ostream& os);

		void display(std::ostream& os) const;
	};

}

#endif // SENECA_CUSTOMERORDER_H
