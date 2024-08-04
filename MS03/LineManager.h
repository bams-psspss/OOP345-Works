// Name: Pattarawan Saravaneeyawong
// Seneca Student ID: 130618234
// Seneca email: psaravaneeyawong@myseneca.ca
// Date of completion: 04 August 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace seneca {
	class LineManager {
		std::vector<Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

	public:
		//Constructor
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);

		//Reorders the workstation
		void reorderStations();

		bool run(std::ostream& os);
		//Display the result
		void display(std::ostream& os) const;
	};
}

#endif // !SENECA_LINEMANAGER_H
