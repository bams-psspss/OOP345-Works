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
