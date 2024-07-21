/***********************************************************************
                        Workshop - 8(Part-2)

Name : Abhishek Vijay Bagul
Email : abagul@myseneca.ca
Student ID : 148451214
Date : 07/21/24

I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.

***********************************************************************/

#include "Database.h"

template <>
void seneca::Database<std::string>::encryptDecrypt(std::string& value);

template <>
void seneca::Database<long long>::encryptDecrypt(long long& value);

template class seneca::Database<std::string>;
template class seneca::Database<long long>;

template <typename T>
std::shared_ptr<seneca::Database<T>> seneca::Database<T>::m_pDatabase = nullptr;