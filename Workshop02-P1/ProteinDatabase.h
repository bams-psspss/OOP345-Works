#ifndef SENECA_PROTEINDATABASE_h
#define SENECA_PROTEINDATABASE_h

#include <string>

namespace seneca {
	class ProteinDatabase {
		std::string* m_proteins;
		size_t m_numProteins;

	public:
		ProteinDatabase();
		ProteinDatabase(const std::string& fname);

		~ProteinDatabase();

		size_t size() const;
		std::string operator[](size_t index);
	};
}

#endif // !SENECA_PROTEINDATABASE_h
