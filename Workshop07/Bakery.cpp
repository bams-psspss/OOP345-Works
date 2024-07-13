/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		13 July 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>

#include "Bakery.h"



namespace seneca {
	Bakery::Bakery(const std::string& fileName)
	{
		std::ifstream theFile(fileName);
		std::string theLine{};
		BakedGood temp{};
		
		if (!theFile.is_open()) {
			throw std::runtime_error ("Bad FILE!!!!\n");
		}
	
		while (std::getline(theFile, theLine)) {
			std::string type = trim(theLine.substr(0, 8));
			std::string desc = trim(theLine.substr(8, 20));
			std::string shelfLife = trim(theLine.substr(28, 14));
			std::string stock = trim(theLine.substr(42, 8));
			std::string price = trim(theLine.substr(50,6));



			if (type == "Bread") {
				temp.type = BakedType::BREAD;
			}
			else {
				temp.type = BakedType::PASTERY;
			}

			temp.desc = desc;
			temp.shelfLife = std::stoi(shelfLife);
			temp.stock = std::stoi(stock);
			temp.price = std::stod(price);


			bakedGood.push_back(temp);

		}
	}




	std::string Bakery::trim(std::string theStr)
	{
		//Return npos if first position is NOT spacebar
		size_t first = theStr.find_first_not_of(' ');

		size_t last = theStr.find_last_not_of(' ');

		if (first == std::string::npos) {
			return theStr; //First char is not space return the aggrument
		}

		return theStr.substr(first, (last - first + 1));
	}

	void Bakery::showGoods(std::ostream& os) const
	{
		 int stock = 0;
		 double price = 0;

		std::for_each(bakedGood.begin(), bakedGood.end(),
			[&os](const BakedGood& b) {
				os << b << '\n';
			}
		);

		std::for_each(bakedGood.begin(), bakedGood.end(), [&stock, &price](const BakedGood& b) {
			stock += b.stock;
			price += b.price;
			}
		
		);
		os << "Total Stock: " << stock << '\n';
		os << "Total Price: " << price << '\n';
	}

	void Bakery::sortBakery(const std::string theField)
	{
		auto func = [theField](const BakedGood& a, const BakedGood& b) {
			bool ret{ false };
			if (theField == "Description") {
				ret = a.desc < b.desc;
			}
			else if (theField == "Shelf") {
				ret = a.shelfLife < b.shelfLife;
			}
			else if (theField == "Stock") {
				ret = a.stock < b.stock;
			}
			else if (theField == "Price") {
				ret = a.price < b.price;
			}
			return ret;
		};

		std::sort(bakedGood.begin(), bakedGood.end(), func);

	}

	std::vector<BakedGood> Bakery::combine(const Bakery& theOther)
	{
		std::vector<BakedGood> ret(bakedGood.size() + theOther.bakedGood.size());
		sortBakery("Price");
		Bakery copy = theOther;
		copy.sortBakery("Price");
		std::merge(theOther.bakedGood.begin(), theOther.bakedGood.end(),
			bakedGood.begin(), bakedGood.end(),
			ret.begin(),
			[](const BakedGood& a, const BakedGood& b) {
				return a.price < b.price;
			});

		return ret;
	}




	bool Bakery::inStock(const std::string& theDesc, const BakedType& theType) const
	{
		return std::any_of(bakedGood.begin(), bakedGood.end(),
			[theDesc, theType](const BakedGood& b) {
				return b.desc == theDesc && b.type == theType && b.stock > 0;
			});
	}

	std::list<BakedGood> Bakery::outOfStock(const BakedType& theType) const {
		std::list<BakedGood> noStock;
		std::copy_if(bakedGood.begin(), bakedGood.end(), std::back_inserter(noStock),
			[theType](const BakedGood& b) {
				return (b.type == theType && b.stock == 0);
			});

		noStock.sort([](const BakedGood& a, const BakedGood& b) {
			return a.price < b.price;
			});

		return noStock;
	}

	


}

std::ostream& operator<<(std::ostream& out, const seneca::BakedGood& b) {
	out << "* " << std::left << std::setw(10)
		<< (b.type == seneca::BakedType::BREAD ? "Bread" : "Pastry")
		<< " * " << std::left << std::setw(20) << b.desc
		<< " * " << std::left << std::setw(5) << b.shelfLife
		<< " * " << std::left << std::setw(5) << b.stock
		<< " * " << std::fixed << std::setprecision(2)
		<< std::right << std::setw(8) << b.price
		<< " * ";
	return out;
}