#include <iostream>
#include <iomanip>
#include <string>
#include "Book.h"

using namespace std;
 
namespace seneca {
	Book::Book() : m_title{}, m_numChapters{}, m_numPages{} {
	}

	Book::Book(const std::string& title, unsigned nChapters, unsigned nPages) :
		m_title{ title }, m_numChapters{ nChapters }, m_numPages{nPages} {
	}

	std::ostream& Book::print(std::ostream& os) const {
		unsigned avgPage = m_numPages / m_numChapters;
		if (m_title != "" && m_numChapters && m_numPages) {
			os << setw(56) << right << m_title << "," << m_numChapters << "," << m_numPages << " | ";
			os << setw(15) << left << avgPage;
		}


		return os;
	}



	std::ostream& operator<<(std::ostream& os, const Book& bk) {
		return bk.print(os);
	}

}