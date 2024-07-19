#include <iostream>
#include <vector>
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;
using namespace seneca;

int main(int argc, char** argv){
	std::cout << "Command Line: " << argv[0];
	for (int i = 1; i < argc; ++i)
		std::cout << " " << argv[i];
	std::cout << std::endl << std::endl;
	/*if (argc < 4) {
		std::cerr << "ERROR: Insufficient number of arguments\n";
		std::exit(1);
	}*/
	CustomerOrder theOrders;
	theOrders.display();
}