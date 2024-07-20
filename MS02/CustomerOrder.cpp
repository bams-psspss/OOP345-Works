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

	/*CustomerOrder::CustomerOrder(const std::string& theStr) {
		Utilities u;
		size_t pos = 0;
		size_t tempPos = 0;
		size_t count = 0;
		bool more = true;

		m_name = u.extractToken(theStr, pos, more);
		m_product = u.extractToken(theStr, pos, more);

		tempPos = pos;

		while (more) {
			u.extractToken(theStr, tempPos, more);
			count++;
		}

		m_cntItem = count;

		delete[] m_lstItem;
		m_lstItem = new Item * [m_cntItem];

		for (size_t i = 0; i < m_cntItem && more; i++) {
			m_lstItem[i]->m_itemName = u.extractToken(theStr, pos, more);
		}

		//??????
		CustomerOrder::m_widthField = std::max(u.getFieldWidth(), CustomerOrder::m_widthField);



	}*/

	CustomerOrder::CustomerOrder(const std::string& theStr) {
		Utilities u;
		size_t pos = 0;
		size_t tempPos = 0;
		size_t count = 0;
		bool more = true;

		m_name = u.extractToken(theStr, pos, more);
		m_product = u.extractToken(theStr, pos, more);

		// Save the current position to count the items
		tempPos = pos;

		// Count the number of items
		while (more) {
			u.extractToken(theStr, tempPos, more);
			count++;
		}

		m_cntItem = count;

		// Allocate memory for the list of items
		m_lstItem = new Item * [m_cntItem];

		// Reset 'more' to true for the next extraction loop
		more = true;

		// Extract item names and initialize Item objects
		for (size_t i = 0; i < m_cntItem && more; ++i) {
			std::string itemName = u.extractToken(theStr, pos, more);
			m_lstItem[i] = new Item(itemName);
		}

		// Update m_widthField if necessary
		CustomerOrder::m_widthField = std::max(u.getFieldWidth(), CustomerOrder::m_widthField);
	}


	CustomerOrder::CustomerOrder(const CustomerOrder& other)
	{
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

	/*CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		//Check for self assignment
		if (this != &other) {
			//Free Resources
			delete[] m_lstItem;

			//Shallow Copy
			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;

			//Move the Resouce
			m_lstItem = new Item * [m_cntItem];

			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = other.m_lstItem[i];
			}

			//Delete the old one
			for (size_t i = 0; i < other.m_cntItem; ++i) {
				delete other.m_lstItem[i];
			}
			delete[] other.m_lstItem;
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
			other.m_name = {};
			other.m_product = {};

		}

		return *this;
	}*/

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		// Check for self-assignment
		if (this != &other) {
			// Free the existing resources of this object
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			// Transfer ownership of the resources from other to this
			m_name = std::move(other.m_name);
			m_product = std::move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			// Nullify the resources of other
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

	/*bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool exist = false;
		bool filled = false;

		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				exist = true;
				if (m_lstItem[i]->m_isFilled && exist) {
					filled = true;
				}
			}

			if (m_lstItem[i]->m_itemName != itemName) {
				exist = true;
			}
		}
		return exist && filled;
		
	}*/

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool itemExists = false;
		bool allFilled = true;

		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				itemExists = true;
				if (!m_lstItem[i]->m_isFilled) {
					allFilled = false;
				}
			}
		}

		return !itemExists || allFilled;
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