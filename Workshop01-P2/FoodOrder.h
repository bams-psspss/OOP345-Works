/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		19 May 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/


#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
	class FoodOrder {
		char m_name[11]{};
		char* m_descFood{nullptr};
		double m_price{};
		bool m_daily{false};

	public:
		FoodOrder();
		//Copy Assignment Operator
		FoodOrder(const FoodOrder& other);

		//Coppy Assignment Operator
		FoodOrder& operator=(const FoodOrder& other);

		//Destructor 
		~FoodOrder();


		std::istream& read(std::istream& is = std::cin);
		std::ostream& display(std::ostream& os = std::cout);

	};
}

#endif // !SENECA_FOODORDER_H
