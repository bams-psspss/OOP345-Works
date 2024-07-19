#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <string>
#include "Station.h"


namespace seneca {

	struct Item {
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder {

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{0};
		Item** m_lstItem{};

		//Display Purpose
		static size_t m_widthField;

	public:
		CustomerOrder();
		//Not Done
		CustomerOrder(const std::string& theStr);

		//Copy Constructor ?? If called throw exception error???
		CustomerOrder(const CustomerOrder& other);
		//Assignment Operator
		CustomerOrder& operator= (const CustomerOrder& other);

		//Move Constructor
		CustomerOrder( CustomerOrder&& other) noexcept;
		//Move Assignment Operator
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;

		~CustomerOrder();

		bool isOrderFilled() const;
		//???? Review it again
		bool isItemFilled(const std::string& itemName) const;
		//Not sure???
		void fillItem(Station& station, std::ostream& os);

		void display(std::ostream& os) const;
	};

}

#endif // SENECA_CUSTOMERORDER_H
