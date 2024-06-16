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
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <string>

namespace seneca {
	class Book
	{
		std::string m_author{};
		std::string m_title{};
		std::string m_country{};
		size_t m_yearPub{};
		double m_price{};
		std::string m_desc{};

	public:
		Book();
		//Constructor receive reference
		Book(const std::string& strBook);


		//Return title
		const std::string& title() const;

		//Return publication country
		const std::string& country() const;

		//Return publication year
		const size_t& year() const;

		//Return price by reference
		double& price();

		//Trim 
		static std::string trim(const std::string& theStr);
		//Helper
		friend std::ostream& operator<<(std::ostream& os, const Book& book);

		//Template
		template <typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_desc);
		}

	};
}


#endif // !SENECA_BOOK_H