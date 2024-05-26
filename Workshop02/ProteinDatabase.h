/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		26 May 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>

namespace seneca {
	class ProteinDatabase {
		std::string* m_proteins{};
		size_t m_numProteins{};

	public:
		ProteinDatabase();
		ProteinDatabase(const std::string& fname);
		ProteinDatabase(const ProteinDatabase& other);
		ProteinDatabase& operator=(const ProteinDatabase& other);

		ProteinDatabase(ProteinDatabase&& other) noexcept;
		ProteinDatabase& operator=(ProteinDatabase&& other) noexcept;

		~ProteinDatabase();

		size_t size() const;
		
		const std::string operator[](size_t index) const;
	};
}

#endif // !SENECA_PROTEINDATABASE_H
