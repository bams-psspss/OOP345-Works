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
		static int stock = 0;
		static double price = 0;
		static double totalPrice = 0.0;

		std::for_each(bakedGood.begin(), bakedGood.end(),
			[&os](const BakedGood& b) {
				os << b << '\n';
			}
		);

		std::for_each(bakedGood.begin(), bakedGood.end(), [](const BakedGood& b) {
			stock += b.stock;
			price += b.price;
			}
		
		);
		os << "Total Stock: " << stock << '\n';
		os << "Total Price: " << price << '\n';
	}
	void Bakery::sortBakery(std::string& theField)
	{
		if (theField == "Description") {
			//Sort Bakery part
			std::sort(bakedGood.begin(), bakedGood.end(),std::less<std::string>());
			

			//bool myfunction(int i, int j) { return (i < j); }


		}
		else if (theField == "Shelf") {

		}
		else  if (theField == "Stock") {
			
		}
		else {

		}
	}
}

//Edit the format!!!!
std::ostream& operator<<(std::ostream& out, const seneca::BakedGood& b) {
	out << "* " << std::left << std::setw(10) << (b.type == seneca::BakedType::BREAD ? "Bread" : "Pastry");
	out << " * " << std::left << std::setw(20) << b.desc;
	out << " * " << std::right << std::setw(5) << b.shelfLife;
	out << " * " << std::right << std::setw(5) << b.stock;
	out << " * " << std::fixed << std::setprecision(2) << std::setw(8) << b.price;
	out << " *";
	return out;
}