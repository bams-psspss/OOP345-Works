/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		21 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include "Database.h"

template <>
void seneca::Database<std::string>::encryptDecrypt(std::string& value);

template <>
void seneca::Database<long long>::encryptDecrypt(long long& value);

template class seneca::Database<std::string>;
template class seneca::Database<long long>;

template <typename T>
std::shared_ptr<seneca::Database<T>> seneca::Database<T>::m_instance = nullptr;