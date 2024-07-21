#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <iomanip>

#include "Database.h"

namespace seneca {

	std::shared_ptr<Database> Database::m_instance = nullptr;
	std::string Database::m_keys[20];
	std::string Database::m_values[20];

	Database::Database(const std::string& filename) {
		std::cout << "[" << this << "] "
			<< "Database(const std::string&)\n";

		//Open da FILE!
		std::ifstream theFile(filename);

		std::string tempKey, tempVal;
		std::string theLine;

		if (!theFile.is_open()) {
			throw std::runtime_error("Bad FILE!!\n");
		}
		while (std::getline(theFile, theLine) && m_numEntries < 20) {
			// Find the first space in the line to split key and value
			size_t spacePos = theLine.find_first_of(' ');
			if (spacePos != std::string::npos) {
				std::string tempKey = theLine.substr(0, spacePos);
				tempKey = trim(tempKey);

				std::string tempVal = theLine.substr(spacePos + 1);
				tempVal = trim(tempVal);

				// Replace underscores in the key with spaces
				std::replace(tempKey.begin(), tempKey.end(), '_', ' ');

				// Store the key and value
				m_keys[m_numEntries] = tempKey;
				m_values[m_numEntries] = tempVal;

				// Increment the number of entries
				m_numEntries++;

	
			}
		}
	}

	std::shared_ptr<Database> Database::getInstance(const std::string& filename)
	{
		if (m_instance == nullptr) {
			m_instance = std::shared_ptr<Database> (new Database(filename));
		}
		return m_instance;
	}

	Err_Status Database::GetValue(const std::string& key, std::string& value)
	{
		for (size_t i = 0; i < m_numEntries; i++) {
			if (key == m_keys[i]) {
				value = m_values[i];
				return Err_Status::Err_Success;
			}
		}
		return Err_Status::Err_NotFound;
	}

	//Doubt
	Err_Status Database::SetValue(const std::string& key, const std::string& value)
	{
		size_t theInd = 0;
		if (m_numEntries < 20) {
			for (size_t i = 0; i < m_numEntries && !(theInd); i++) {
				if (m_keys[i].empty() && m_values[i].empty()) {
					theInd = i;
				}
			}
			m_keys[theInd] = key;
			m_values[theInd] = value;
			
			m_numEntries++;
			return Err_Status::Err_Success;
		}

		return Err_Status::Err_OutOfMemory;
	}
	std::string Database::trim(std::string theStr)
	{
		//Return npos if first position is NOT spacebar
		size_t first = theStr.find_first_not_of(' ');

		size_t last = theStr.find_last_not_of(' ');

		if (first == std::string::npos) {
			return theStr; //First char is not space return the aggrument
		}

		return theStr.substr(first, (last - first + 1));
	}
	Database::~Database()
	{
		std::cout << "[" << m_instance << "] ~Database()";


		std::ofstream file(m_fileName + ".bkp.txt");
		for (size_t i = 0; i < m_numEntries; i++)
		{
			file << std::setw(25) << std::left << m_keys[i] 
				<< "-> " << m_values[i] << std::endl;
		}

	}
}

