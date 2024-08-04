#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace seneca {
	class LineManager {
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

	public:
		//This -- TRY
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);

		//Reorders the workstation present in 
		//This
		void reorderStations();


		//This
		bool run(std::ostream& os);



		void display(std::ostream& os) const;
	};
}

#endif // !SENECA_LINEMANAGER_H
