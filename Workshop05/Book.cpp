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
#include <string>
#include <iomanip>
#include "Book.h"

using namespace std;

namespace seneca {
	Book::Book() : m_author{}, m_title{}, m_country{}, m_yearPub{ 0 }, 
		m_price{ 0.0 }, m_desc{}
	{
	}
	Book::Book(const std::string& strBook)
	{
		size_t start = 0;
		size_t end = strBook.find(',');

		m_author = trim(strBook.substr(start, end - start));

		start = end + 1;
		end = strBook.find(',', start);
		m_title = trim(strBook.substr(start, end - start));

		start = end + 1;
		end = strBook.find(',', start);
		m_country = trim(strBook.substr(start, end - start));

		start = end + 1;
		end = strBook.find(',', start);
		m_price = std::stod(trim(strBook.substr(start, end - start)));

		start = end + 1;
		end = strBook.find(',', start);
		m_yearPub = std::stoul(trim(strBook.substr(start, end - start)));

		start = end + 1;
		m_desc = trim(strBook.substr(start));
	}
	const std::string& Book::title() const
	{
		return m_title;
	}
	const std::string& Book::country() const
	{
		return m_country;
	}
	const size_t& Book::year() const
	{
		return m_yearPub;
	}
	double& Book::price()
	{
		return m_price;
	}


	string Book::trim(const string& theStr)
	{
		//Return npos if first position is NOT spacebar
		size_t first = theStr.find_first_not_of(' ');

		size_t last = theStr.find_last_not_of(' ');

		if (first == string::npos) {
			return theStr; //First char is not space return the aggrument
		}

		return theStr.substr(first, (last - first + 1));
	}

	std::ostream& operator<<(std::ostream& os, const Book& book) {
		os  << std::setw(20) << std::right << book.m_author << " | "
			<< std::setw(22) << std::right << book.m_title << " | "
			<< std::setw(5) << std::right << book.m_country << " | "
			<< std::setw(4) << std::right << book.m_yearPub << " | "
			<< std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
			<< book.m_desc << endl;
		return os;
	}
}
