/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		13 July 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace seneca {
	enum class BakedType {
		BREAD, 
		PASTERY
	};

	struct BakedGood {
		BakedType type;
		std::string desc;
		int shelfLife;
		int stock;
		double price;
	};

	class Bakery {
		std::vector<BakedGood> bakedGood;

	public:
		Bakery(const std::string& fileName);

		//Trim the whitespaces
		std::string trim(std::string theString);

		void showGoods(std::ostream& os) const;

		void sortBakery(const std::string theField);

		
		std::vector<BakedGood> combine(const Bakery& theOther);

		//Check instock items
		bool inStock(const std::string& theDesc, const BakedType& theType) const;

		//Return out of stock items
		std::list<BakedGood> outOfStock(const BakedType& theType) const;

		~Bakery() = default;
	};
}
std::ostream& operator<<(std::ostream& out, const seneca::BakedGood& b);


#endif // !SENECA_BAKERY_H

