// Name: Pattarawan Saravaneeyawong
// Seneca Student ID: 130618234
// Seneca email: psaravaneeyawong@myseneca.ca
// Date of completion: 13 July 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {
	class Utilities {
		size_t m_widthField{1};

		static char m_delimiter;

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;

		//Not Done
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter);
		static char getDelimiter();

		std::string trim(std::string theStr);

		
	};
}



#endif // !SENECA_UTILITIES_H
