/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		16 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include <iomanip>
#include "Movie.h"

using namespace std;
namespace seneca {

    Movie::Movie() : m_title{}, m_year{ 0 }, m_desc{} {}

    Movie::Movie(const std::string& strMovie) {
        size_t start = 0;
        size_t end = strMovie.find(',');

        m_title = trim(strMovie.substr(start, end - start));

        start = end + 1;
        end = strMovie.find(',', start);
        m_year = std::stoul(trim(strMovie.substr(start, end - start)));

        start = end + 1;
        m_desc = trim(strMovie.substr(start));
    }

    const std::string& Movie::title() const {
        return m_title;
    }

    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << std::setw(40) << std::right << movie.m_title << " | "
            << std::setw(4) << movie.m_year << " | "
            << movie.m_desc << endl;
        return os;
    }

    std::string Movie::trim(const std::string& theStr)
    {
        //Return npos if first position is NOT spacebar
        size_t first = theStr.find_first_not_of(' ');

        size_t last = theStr.find_last_not_of(' ');

        if (first == string::npos) {
            return theStr; //First char is not space return the aggrument
        }

        return theStr.substr(first, (last - first + 1));
    }


} 