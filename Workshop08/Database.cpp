#include "Database.h"

// Explicit template instantiation for specific types
template class seneca::Database<std::string>;
template class seneca::Database<long long>;

// Explicit template specialization for encrypt/decrypt methods
template <>
void seneca::Database<std::string>::encryptDecrypt(std::string& value);

template <>
void seneca::Database<long long>::encryptDecrypt(long long& value);
