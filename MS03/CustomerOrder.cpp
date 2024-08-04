// Name: Pattarawan Saravaneeyawong
// Seneca Student ID: 130618234
// Seneca email: psaravaneeyawong@myseneca.ca
// Date of completion: 04 August 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {
    size_t CustomerOrder::m_widthField{};

    CustomerOrder::CustomerOrder() : m_name{}, m_product{},
        m_cntItem{ 0 }, m_lstItem{ nullptr } {}


    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities u;
        size_t pos = 0u;
        bool more = true;
        if (more) {
            m_name = u.extractToken(str, pos, more);
            m_product = u.extractToken(str, pos, more);
        }
        std::vector<std::string> strArr;
        while (more) {
            strArr.push_back(u.extractToken(str, pos, more));
        }
        m_cntItem = strArr.size();

        if (m_cntItem) {
            m_lstItem = new Item * [m_cntItem];

            for (size_t i = 0u; i < m_cntItem; i++) {
                m_lstItem[i] = new Item(strArr[i]);
            }
        }

        if (m_widthField < u.getFieldWidth()) {
            m_widthField = u.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw std::runtime_error("Copy constructor not allowed.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
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

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        bool done{ false };

        for (size_t i = 0; i < m_cntItem && !done; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName()) {
                if (!m_lstItem[i]->m_isFilled && station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    done = true;

                    os << "    Filled " << m_name << ", " << m_product << " ["
                        << m_lstItem[i]->m_itemName << ']' << std::endl;
                }
                else if (!m_lstItem[i]->m_isFilled && station.getQuantity() == 0) {
                    os << "    Unable to fill " << m_name << ", " << m_product << " ["
                        << m_lstItem[i]->m_itemName << ']' << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;

        for (size_t i = 0; i < m_cntItem; i++) {
            os << '[' << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ');
            os << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - " << std::right;
            if (m_lstItem[i]->m_isFilled) {
                os << "FILLED" << std::endl;
            }
            else {
                os << "TO BE FILLED" << std::endl;
            }
        }
    }

}