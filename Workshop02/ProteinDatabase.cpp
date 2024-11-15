/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		26 May 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include <fstream>
#include "ProteinDatabase.h"

using namespace std;

namespace seneca {
	ProteinDatabase::ProteinDatabase() :m_proteins{ nullptr }, m_numProteins{ 0 } {
	}

	
	ProteinDatabase::ProteinDatabase(const std::string& fname) :m_proteins{ nullptr }, m_numProteins{ 0 } {

		ifstream file(fname);
		string theLine;
		string currentProtein;
		size_t index = 0;


		if (!file) {
			cout << "Error to Open the File: " << fname << endl;
		}
		else {
			while (getline(file, theLine)) {
				if (theLine.size() > 0 && theLine[0] == '>') {
					m_numProteins++;
				}
			}

			m_proteins = new string[m_numProteins];

			file.clear();
			file.seekg(0);

			while (getline(file, theLine)) {
				if (theLine[0] == '>') {
					if (index < m_numProteins) {
						index++;
					}
				}
				else {
					if (index > 0 && index <= m_numProteins) {
						m_proteins[index - 1] += theLine;
					}
				}
			}

			file.close();
		}

	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) {
		*this = other;
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& other) {
		if (this != &other) {
			delete[] m_proteins;
			m_numProteins = other.m_numProteins;

			if (m_numProteins > 0) {
				m_proteins = new string[m_numProteins];
				for (auto i = 0u; i < m_numProteins; i++) {
					m_proteins[i] = other.m_proteins[i];
				}
			}
			else {
				m_proteins = nullptr;
				m_numProteins = 0;
			}
		}

		return *this;
	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) noexcept {
		*this = move(other);
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& other) noexcept {
		if (this != &other) {
			delete[] m_proteins;

			m_numProteins = other.m_numProteins;
			m_proteins = other.m_proteins;

			other.m_proteins = nullptr;
			other.m_numProteins = 0;
		}
		return *this;
	}

	ProteinDatabase::~ProteinDatabase() {
		delete[] m_proteins;
	}

	size_t ProteinDatabase::size() const {
		return m_numProteins;
	}


	const std::string ProteinDatabase::operator[](size_t index) const {
		if (index < m_numProteins) {
			return m_proteins[index];
		}
		return "";
	}
}
