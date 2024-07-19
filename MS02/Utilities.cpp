// Name: Pattarawan Saravaneeyawong
// Seneca Student ID: 130618234
// Seneca email: psaravaneeyawong@myseneca.ca
// Date of completion: 13 July 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Utilities.h"



namespace seneca {
	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string temp{};
		size_t len;

		if (next_pos >= str.length()) {
			more = false;
			return "";
		}

		if (str[next_pos] == m_delimiter) {
			more = false;
			throw std::runtime_error("Delimiter at next_pos");
		}

		size_t delimPos = str.find(m_delimiter, next_pos);

		if (delimPos == std::string::npos) {
			temp = str.substr(next_pos);
			next_pos = str.length();
		} else {
			temp = str.substr(next_pos, delimPos - next_pos);
			next_pos = delimPos + 1;
		}

		temp = trim(temp);
		len = temp.length();
		if (len > m_widthField) {
			m_widthField = len;
		}

		more = next_pos < str.length();

		return temp;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
	std::string Utilities::trim(std::string theStr)
	{
		//Return npos if first position is NOT spacebar
		size_t first = theStr.find_first_not_of(' ');

		size_t last = theStr.find_last_not_of(' ');

		if (first == std::string::npos) {
			return theStr; //First char is not space return the aggrument
		}

		return theStr.substr(first, (last - first + 1));
	}
} 