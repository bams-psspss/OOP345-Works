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
#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include "Reservation.h"
#include <iostream>

namespace seneca {
    class ConfirmationSender {
        const Reservation** m_reservations{};
        size_t m_cnt{};

    public:
        ConfirmationSender();

        ConfirmationSender(const ConfirmationSender& other);
        ConfirmationSender& operator=(const ConfirmationSender& other);

        ConfirmationSender(ConfirmationSender&& other) noexcept;
        ConfirmationSender& operator=(ConfirmationSender&& other) noexcept;

        ~ConfirmationSender();

        ConfirmationSender& operator+=(const Reservation& res);
        ConfirmationSender& operator-=(const Reservation& res);

        friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& cs);
    };
}

#endif //SENECA_CONFIRMATIONSENDER_H
