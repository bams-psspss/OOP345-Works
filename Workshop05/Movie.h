/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		16 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#pragma once
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include <iostream>

namespace seneca {

    class Movie {
        std::string m_title;
        size_t m_year;
        std::string m_desc;

    public:
        Movie();

        Movie(const std::string& strMovie);

        const std::string& title() const;

        static std::string trim(const std::string& theStr);


        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_desc);
        }

        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    };

} 

#endif // SENECA_MOVIE_H
