/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		19 May 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include "FoodOrder.h"

using namespace std;

double g_taxrate = 0.0;
double g_dailydiscount = 0.0;

namespace seneca {
	FoodOrder::FoodOrder() : m_price{ 0.0 }, m_daily{ false } {
		m_name[0] = '\0';
		m_descFood[0] = '\0';
	}

	std::istream& FoodOrder::read(std::istream& is) {
		char tempDaily{};
		if (!is.fail()) {
			is.getline(m_name, 11, ',');
			is.getline(m_descFood, 26, ',');

			is >> m_price;			
			is.ignore();

			is >> tempDaily;
			m_daily = (tempDaily == 'Y');
			is.ignore(100, '\n');
			

		}

		return is;
	}


	std::ostream& FoodOrder::display(std::ostream& os)  {
		double totalPrice = (m_price * g_taxrate) + m_price;
		static int count = 0;
		count++;

		os.width(2);
		os.setf(ios::left);
		os << count << ". ";
	
		if (m_name[0]) {
		
			os.width(10);
			os << m_name << "|";

			os.width(25);
			os << m_descFood << "|";

			os.width(12);
			os.precision(2);
			os.setf(ios::fixed);
			os << totalPrice << "|";


			if (m_daily) {
				os.width(13);
				os.setf(ios::right);
				os << totalPrice - g_dailydiscount;
				os.unsetf(ios::right);
			}
			
			os << "\n";
		}
		else {
			os.width(2);
			os.setf(ios::left);
			os << "No Order\n";
		}

		

		return os;
	}



}


