#include <iostream>
#include <fstream>
#include "SpellChecker.h"

using namespace std;

namespace seneca {

    SpellChecker::SpellChecker(const char* filename) 
    {
        std::ifstream file(filename);
        if (!file) {
            throw "Bad file name!";
        }

        std::string line;
        size_t index = 0;
        while (std::getline(file, line) && index < 6) {
            size_t pos = line.find(' ');
            m_badWords[index] = line.substr(0, pos);

            size_t startPos = pos;
            while (line[startPos] == ' ') startPos++;
            m_goodWords[index] = line.substr(startPos);
            ++index;
        }
    }

    void SpellChecker::operator()(std::string& text) 
    {
        for (size_t i = 0; i < 6; ++i) {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacements[i]++;
                pos += m_goodWords[i].length();
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const {
        for (size_t i = 0; i < 6; i++) {
            out.width(15);
            out << std::right << m_badWords[i] << ": "
                << m_replacements[i] << " replacements" << std::endl;
        }
    }

}
