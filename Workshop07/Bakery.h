#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <iostream>
#include <string>
#include <vector>

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

		std::string trim(std::string theString);

		void showGoods(std::ostream& os) const;

		void sortBakery(std::string& theField);


	};
}
std::ostream& operator<<(std::ostream& out, const seneca::BakedGood& b);


#endif // !SENECA_BAKERY_H

