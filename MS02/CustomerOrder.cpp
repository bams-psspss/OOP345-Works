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
		bool more = true;
		size_t pos = 0;
		size_t count = 0;
		size_t index = 0;
		std::string itemName;


		u.setDelimiter('|');

		m_name = u.extractToken(theStr, pos, more);
		m_product = u.extractToken(theStr, pos, more);

		//Index save point
		index = pos;

		//Count how many items are there
		while (more) {
			u.extractToken(theStr, pos, more);
			if (more) {
				count++;
			}
		}
		m_cntItem = count;
		m_lstItem = new Item*[m_cntItem];
		more = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			itemName = u.extractToken(theStr, index, more);
			m_lstItem[i] = new Item(itemName);
		}

		if (u.getFieldWidth() > m_widthField) {
			m_widthField = u.getFieldWidth();
		}
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

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
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
			m_lstItem = other.m_lstItem;

			//Delete the old one
			//BC --> 1
			delete[] other.m_lstItem;
	
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		//Because it is ARRAY!
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
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
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				//Found the name
				if (station.getQuantity() > 0) {
					//Subtract 1 from inventory
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << "Filled " << m_name << 
						", PRODUCT " << m_lstItem[i]->m_itemName << '\n';
				}
				else {
					//Is Handled but unfilled
					if (station.getQuantity() < 0) {
						os << "Unanble to fill " << m_name << 
							", PRODUCT " << m_lstItem[i]->m_itemName << '\n';
					}
				}

			}
		
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << '\n';
		for (size_t i = 0; i < m_cntItem; i++) {
			os << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber
				<< std::setw(m_widthField) << m_lstItem[i]->m_itemName
				<< (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << '\n';
		}
		
	}

}