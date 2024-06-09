/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		08 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include "ConfirmationSender.h"

namespace seneca {
    ConfirmationSender::ConfirmationSender() : m_reservations{ nullptr }, m_cnt{ 0 } {}

    ConfirmationSender::ConfirmationSender(const ConfirmationSender& other) : m_reservations{ nullptr }, m_cnt{ other.m_cnt } {
        if (m_cnt > 0) {
            m_reservations = new const Reservation * [m_cnt];
            for (size_t i = 0; i < m_cnt; ++i) {
                m_reservations[i] = other.m_reservations[i];
            }
        }
    }

    ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other) {
        if (this != &other) {
            delete[] m_reservations;
            m_cnt = other.m_cnt;
            m_reservations = new const Reservation * [m_cnt];
            for (size_t i = 0; i < m_cnt; ++i) {
                m_reservations[i] = other.m_reservations[i];
            }
        }
        return *this;
    }

    ConfirmationSender::ConfirmationSender(ConfirmationSender&& other) noexcept : m_reservations{ other.m_reservations }, m_cnt{ other.m_cnt } {
        other.m_reservations = nullptr;
        other.m_cnt = 0;
    }

    ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other) noexcept {
        if (this != &other) {
            delete[] m_reservations;
            m_reservations = other.m_reservations;
            m_cnt = other.m_cnt;
            other.m_reservations = nullptr;
            other.m_cnt = 0;
        }
        return *this;
    }

    ConfirmationSender::~ConfirmationSender() {
        delete[] m_reservations;
    }

    ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_reservations[i] == &res) {
                return *this;
            }
        }

        const Reservation** temp = new const Reservation * [m_cnt + 1];
        for (size_t i = 0; i < m_cnt; ++i) {
            temp[i] = m_reservations[i];
        }
        temp[m_cnt] = &res;
        delete[] m_reservations;
        m_reservations = temp;
        ++m_cnt;

        return *this;
    }


    ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
    
        size_t index = m_cnt;
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_reservations[i] == &res) {
                index = i;
                break;
            }
        }

        if (index == m_cnt) {
            return *this;  
        }

        const Reservation** temp = new const Reservation * [m_cnt - 1];
        for (size_t i = 0, j = 0; i < m_cnt; ++i) {
            if (i != index) {
                temp[j++] = m_reservations[i];
            }
        }
        delete[] m_reservations;
        m_reservations = temp;
        --m_cnt;

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const ConfirmationSender& cs) {
        os << "--------------------------" << std::endl;
        os << "Confirmations to Send" << std::endl;
        os << "--------------------------" << std::endl;

        if (cs.m_cnt == 0) {
            os << "There are no confirmations to send!" << std::endl;
        }
        else {
            for (size_t i = 0; i < cs.m_cnt; ++i) {
                os << *cs.m_reservations[i];
            }
        }

        os << "--------------------------" << std::endl;
        return os;
    }
}
