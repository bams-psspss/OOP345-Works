/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		02 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code 
that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <string>

namespace seneca
{
	class Book
	{
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);


		std::string getTitle() const;
		unsigned getNumChapters() const;
		unsigned getNumPages() const;
		
		double avgPage() const;

		std::ostream& print(std::ostream& os) const;
		bool operator<(const Book& other) const;
		bool operator>(const Book& other) const;

	};
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}



#endif // SENECA_BOOK_H
