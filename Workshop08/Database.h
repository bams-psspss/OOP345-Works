#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>

namespace seneca {

    enum class Err_Status
    {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    template <typename T>
    class Database {
        size_t m_numEntries{};
        static std::shared_ptr<Database<T>> m_instance;
        static std::string m_keys[20];
        static T m_values[20];
        std::string m_fileName{};

        Database(const std::string& filename);
        void encryptDecrypt(T& value);

    public:
        static std::shared_ptr<Database<T>> getInstance(const std::string& filename);

        Err_Status GetValue(const std::string& key, T& value);
        Err_Status SetValue(const std::string& key, const T& value);

        std::string trim(std::string theString);
        ~Database();
    };

    // Template member definitions

    template <typename T>
    std::shared_ptr<Database<T>> Database<T>::m_instance = nullptr;

    template <typename T>
    std::string Database<T>::m_keys[20];

    template <typename T>
    T Database<T>::m_values[20];

    template <typename T>
    Database<T>::Database(const std::string& filename) {
        std::cout << "[" << this << "] Database(const std::string&)\n";

        std::ifstream theFile(filename);
        std::string tempKey, tempVal;
        std::string theLine;

        if (!theFile.is_open()) {
            throw std::runtime_error("Bad FILE!!\n");
        }

        while (std::getline(theFile, theLine) && m_numEntries < 20) {
            size_t spacePos = theLine.find_first_of(' ');
            if (spacePos != std::string::npos) {
                tempKey = theLine.substr(0, spacePos);
                tempKey = trim(tempKey);

                tempVal = theLine.substr(spacePos + 1);
                tempVal = trim(tempVal);

                std::replace(tempKey.begin(), tempKey.end(), '_', ' ');

                m_keys[m_numEntries] = tempKey;

                std::istringstream ss(tempVal);
                T tempValue;
                ss >> tempValue;

                encryptDecrypt(tempValue);
                m_values[m_numEntries] = tempValue;

                m_numEntries++;
            }
        }
    }

    template <typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& filename) {
        if (m_instance == nullptr) {
            m_instance = std::shared_ptr<Database<T>>(new Database<T>(filename));
        }
        return m_instance;
    }

    template <typename T>
    Err_Status Database<T>::GetValue(const std::string& key, T& value) {
        for (size_t i = 0; i < m_numEntries; i++) {
            if (key == m_keys[i]) {
                value = m_values[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    template <typename T>
    Err_Status Database<T>::SetValue(const std::string& key, const T& value) {
        if (m_numEntries < 20) {
            m_keys[m_numEntries] = key;
            m_values[m_numEntries] = value;
            m_numEntries++;
            return Err_Status::Err_Success;
        }
        return Err_Status::Err_OutOfMemory;
    }

    template <typename T>
    std::string Database<T>::trim(std::string theStr) {
        size_t first = theStr.find_first_not_of(' ');
        size_t last = theStr.find_last_not_of(' ');

        if (first == std::string::npos) {
            return theStr;
        }

        return theStr.substr(first, (last - first + 1));
    }

    template <typename T>
    void Database<T>::encryptDecrypt(T& value) {
        // Default implementation does nothing
    }

    template <>
    void Database<std::string>::encryptDecrypt(std::string& value) {
        const char secret[]{ "secret encryption key" };

        for (char& c : value) {
            for (char k : secret) {
                c = c ^ k;
            }
        }
    }

    template <>
    void Database<long long>::encryptDecrypt(long long& value) {
        const char secret[]{ "super secret encryption key" };

        char* bytePtr = reinterpret_cast<char*>(&value);
        for (std::size_t i = 0; i < sizeof(long long); ++i) {
            for (char k : secret) {
                bytePtr[i] = bytePtr[i] ^ k;
            }
        }
    }

    template <typename T>
    Database<T>::~Database() {
        std::cout << "[" << this << "] ~Database()\n";

        std::ofstream file(m_fileName + ".bkp.txt");
        for (size_t i = 0; i < m_numEntries; i++) {
            file << std::setw(25) << std::left << m_keys[i]
                << "-> " << m_values[i] << std::endl;
        }
    }
}

#endif // SENECA_DATABASE_H
