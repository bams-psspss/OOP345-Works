#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <iostream>
#include <memory>
#include <vector>

namespace seneca {

	enum class Err_Status
	{
		Err_Success,
		Err_NotFound,
		Err_OutOfMemory,
	};

	class Database {
		size_t m_numEntries{};

		//Statically-allocated means the size cannot be change
		//So no std::vector (vector can change size of array)
		static std::string m_keys[20];
		static std::string m_values[20];
		std::string m_fileName{};

		//Shared pointer with the type of Databse
		static std::shared_ptr<Database> m_instance;

		//Constructor //Not done yet
		Database(const std::string& filename);

		template <typename T>
		void encryptDecrypt(T& value);

		
	public:
		static std::shared_ptr<Database> getInstance(const std::string& filename);

		//Find matching key with m_key and put set m_value to value
		Err_Status GetValue(const std::string& key, std::string& value);

		//Insert value if the m_numEntries less than 20
		//Doubt
		Err_Status SetValue(const std::string& key, const std::string& value);

		//This too
		~Database();

	};
}





#endif // !SENECA_DATABASE_H
