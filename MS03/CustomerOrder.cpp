// Name: Pattarawan Saravaneeyawong
// Seneca Student ID: 130618234
// Seneca email: psaravaneeyawong@myseneca.ca
// Date of completion: 20 Juy 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>

#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() : m_name{}, m_product{}, 
		m_cntItem{ 0 }, m_lstItem{nullptr}
	{
	}

	CustomerOrder::CustomerOrder(const std::string& theStr) {
		Utilities u;
		size_t pos = 0;
		size_t tempPos = 0;
		size_t count = 0;
		bool more = true;

		//Get the first 2 token
		m_name = u.extractToken(theStr, pos, more);
		m_product = u.extractToken(theStr, pos, more);

		//POS Savepoint
		tempPos = pos;

		//Use tempPos, to literally count how many things are there
		while (more) {
			u.extractToken(theStr, tempPos, more);
			count++;
		}

		m_cntItem = count;

		//Allocate Item POINTERS
		m_lstItem = new Item * [m_cntItem];

		//MORE TO TRUE AGAIN
		more = true;

		// Extract item names and initialize Item objects
		for (size_t i = 0; i < m_cntItem && more; ++i) {
			//POS -> continue where we left after extracting m_product
			std::string itemName = u.extractToken(theStr, pos, more);
			//Initialize the Item, with 1 agrument (THE NAME)
			m_lstItem[i] = new Item(itemName);
		}

		if (u.getFieldWidth() > CustomerOrder::m_widthField) {
			CustomerOrder::m_widthField = u.getFieldWidth();
		}
	}


	CustomerOrder::CustomerOrder(const CustomerOrder& other)
	{
		//THROW!!!! IT IS NOT ALLOW!!!!!!!
		throw std::runtime_error("CANNOT USE COPY!");
	}

	CustomerOrder& CustomerOrder::operator=(const CustomerOrder& other)
	{
		if (this != &other) {
			// Handle assignment logic and throw exception if needed
			throw std::runtime_error("Assignment operator not allowed.");
		}
		return *this;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
	{
		*this = std::move(other);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		// Check for SELF-ASSIGNMENT
		if (this != &other) {
			//FREE THE RESOURCES
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			//MORE EFFICIENT TO USE MOVE
			m_name = std::move(other.m_name);
			m_product = std::move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			//FREE THE 'OTHER'
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
		}
		return *this;
	}


	CustomerOrder::~CustomerOrder()
	{
		//Because it is ARRAY!
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem && filled; i++) {
			if (!(m_lstItem[i]->m_isFilled)) {
				filled = false;
			}
		}
		return filled;

	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		size_t cntFound{}, cntFilled{};
		bool done{ false };

		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				cntFound++;

				if (m_lstItem[i]->m_isFilled == true) {
					cntFilled++;
				}
			}
		}

		if (cntFound == cntFilled || cntFound == 0) {
			done = true;
		}
		return done;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool itemFilled = false;
		
		for (size_t i = 0; i < m_cntItem && !itemFilled; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				//Found the name
				if (station.getQuantity() > 0) {
					//Subtract 1 from inventory
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << "    Filled " << m_name << 
						", " << m_product <<
						" [" << m_lstItem[i]->m_itemName << "]" << '\n';
				}
				else {
					//Is Handled but unfilled
					if (station.getQuantity() < 0) {
						os << "    Unanble to fill " << m_name << 
							", " << m_product << 
							" [" << m_lstItem[i]->m_itemName << "]" <<'\n';
					}
				}

				itemFilled = true;
			}
		
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << '\n';
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ')
				<< std::setw(m_widthField) << m_lstItem[i]->m_itemName
				<< (m_lstItem[i]->m_isFilled ? " - FILLED" : " - TO BE FILLED") << '\n';
		}
		
	}

}