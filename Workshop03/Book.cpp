/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		02 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code 
that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include "Book.h"

using namespace std;

namespace seneca
{
	Book::Book() : m_title{}, m_numChapters{}, m_numPages{} {
	}

	Book::Book(const std::string& title, unsigned nChapters, unsigned nPages) :
		m_title{ title }, m_numChapters{ nChapters }, m_numPages{ nPages } {
	}

	std::string Book::getTitle() const {
		return m_title;
	}

	unsigned Book::getNumChapters() const {
		return m_numChapters;
	}

	unsigned Book::getNumPages() const {
		return m_numPages;
	}

	double Book::avgPage() const
	{
		return static_cast<double>(m_numPages) / m_numChapters;
	}


	std::ostream& Book::print(std::ostream& os) const {
		if (!m_title.empty() && m_numChapters != 0 && m_numPages != 0) {
			os << std::right << std::setw(56) << m_title + "," + std::to_string(m_numChapters) + "," + std::to_string(m_numPages);
			os << " | " << "(" << std::setw(14) << std::left << std::to_string(avgPage()) + ")";
		}
		else {
			os << "| Invalid book data";
		}

		return os;
	}
	bool Book::operator<(const Book& other) const {
		return avgPage() < other.avgPage();
	}

	bool Book::operator>(const Book& other) const {
		return avgPage() > other.avgPage();
	}


	std::ostream& operator<<(std::ostream& os, const Book& bk) {
		return bk.print(os);
	}

}
