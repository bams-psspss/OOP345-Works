#include <iostream>
#include <fstream>
#include "ProteinDatabase.h"

using namespace std;

namespace seneca {
	ProteinDatabase::ProteinDatabase() :m_proteins{nullptr}, m_numProteins{0} { 
	}

	//Not done
	ProteinDatabase::ProteinDatabase(const std::string& fname) :m_proteins{ nullptr }, m_numProteins{0} {

		ifstream file(fname);
		string theLine;
		string currentProtein;
		size_t index = 0;
		bool sequence = false;


		if (!file) {
			cout << "Error to Open the File: " << fname << endl;
		}
		else {
			while (getline(file, theLine)) {
				if (theLine.size() > 0 && theLine[0] == '>') {
					m_numProteins++;
				}
			}
			file.clear();
			file.seekg(0);

			m_proteins = new string[m_numProteins];

			while (getline(file, theLine)) {
				if (!theLine.empty() && theLine[0] == '>') {
					if (sequence && !currentProtein.empty()) {
						m_proteins[index++] = currentProtein;
						currentProtein.clear();
					}
					sequence = true;
				}
				else if (sequence) {
					currentProtein += theLine;
				}
			}

			file.close();
		}

	}

	ProteinDatabase::~ProteinDatabase() {
		delete[] m_proteins;
	}

	size_t ProteinDatabase::size() const {
		return m_numProteins;
	}


	std::string ProteinDatabase::operator[](size_t index) {
		string result = "";
		if (index < m_numProteins) {
			result = m_proteins[index];
		}
		return result;
	}
}