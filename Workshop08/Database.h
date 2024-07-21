/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		21 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/

#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

namespace seneca {

    enum class Err_Status
    {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    template <typename T>
    class Database
    {
    private:
        static std::shared_ptr<Database<T>> m_instance;

        size_t m_size = 0;

        std::string m_keys[20];

        T m_values[20];

        std::string m_file;

        Database(const std::string& filename);

        void encryptDecrypt(T& value);

    public:
        Database() = delete;

        static std::shared_ptr<Database<T>> getInstance(const std::string& filename);

        Err_Status GetValue(const std::string& key, T& value);
        Err_Status SetValue(const std::string& key, const T& value);

        ~Database();
    };

    template <typename T>
    Database<T>::Database(const std::string& filename) : m_size(0), m_keys{}, m_values{}, m_file(filename)
    {
        std::cout << "[" << this << "] Database(const std::string&)" << std::endl;

        std::ifstream file(filename);
        size_t i = 0;

        while (file && i < 20)
        {
            std::string temp;
            getline(file, temp, ' ');

            while (temp.find('_') != std::string::npos)
            {
                temp.replace(temp.find('_'), 1, " ");
            }
            m_keys[i] = temp;

            T tempValues;
            file >> tempValues;
            encryptDecrypt(tempValues);
            m_values[i] = tempValues;
            file.ignore();
            ++i;
        }

        m_file = filename;
        m_size = i;
    }

    template <typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& filename)
    {
        if (m_instance == nullptr)
        {
            m_instance = std::shared_ptr<Database<T>>(new Database<T>(filename));
        }
        return m_instance;
    }

    template <typename T>
    void Database<T>::encryptDecrypt(T& value)
    {
        //LITERALLY DOING NOTHING
    }

    template <>
    void Database<std::string>::encryptDecrypt(std::string& value)
    {
        const char secret[]{ "secret encryption key" };

        for (char& c : value)
        {
            for (char k : secret)
            {
                c = c ^ k;
            }
        }
    }

    template <>
    void Database<long long>::encryptDecrypt(long long& value)
    {
        const char secret[]{ "super secret encryption key" };

        char* bytePtr = reinterpret_cast<char*>(&value);
        for (std::size_t i = 0; i < sizeof(long long); ++i)
        {
            for (char k : secret)
            {
                bytePtr[i] = bytePtr[i] ^ k;
            }
        }
    }

    template <typename T>
    Err_Status Database<T>::GetValue(const std::string& key, T& value)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (key == m_keys[i])
            {
                value = m_values[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    template <typename T>
    Err_Status Database<T>::SetValue(const std::string& key, const T& value)
    {
        if (m_size < 20)
        {
            m_keys[m_size] = key;
            m_values[m_size] = value;
            ++m_size;
            return Err_Status::Err_Success;
        }
        return Err_Status::Err_OutOfMemory;
    }

    template <typename T>
    Database<T>::~Database()
    {
        std::cout << "[" << this << "] ~Database()" << std::endl;
        std::ofstream file(m_file + ".bkp.txt");

        for (size_t i = 0; i < m_size; ++i)
        {
            file.width(25);
            file.fill(' ');
            file.setf(std::ios::left);
            file << m_keys[i];
            file.unsetf(std::ios::left);
            encryptDecrypt(m_values[i]);
            file << " -> " << m_values[i] << std::endl;
        }
    }
}

#endif //SENECA_DATABASE_H
