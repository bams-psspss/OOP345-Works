// Workshop 9 - Multi-Threading, Thread Class
/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		27 July 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <thread>
#include "ProcessData.h"

namespace seneca
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++)
		{
			//Add this!
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++)
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr && num_threads>0 && averages && variances && p_indices;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples.
	ProcessData::ProcessData(const std::string& filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.

		//Open the file in binary mode
		std::ifstream theFile(filename, std::ios::binary);

		//Check if the file is open
		if (theFile.is_open()) {

			//Cast total_items into char* because .read() receive char* in the first parameter
			//read and store it in the total_items -> firs int data is number of data
			theFile.read(reinterpret_cast<char*>(&total_items), sizeof(int));

			//Allocate the data with the number of the items
			data = new int[total_items];

			//This one read an actual data from .bin file
			//store it in data memeber
			theFile.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

			//CLOSE!
			theFile.close();

		}




		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]\n";

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads+1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}

	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the
	//   function logic for the computation of average and variance by running the
	//   functions `computeAvgFactor` and `computeVarFactor` in multiple threads.
	// The function divides the data into a number of parts, where the number of parts is
	//   equal to the number of threads. Use multi-threading to compute average-factor for
	//   each part of the data by calling the function `computeAvgFactor`. Add the obtained
	//   average-factors to compute total average. Use the resulting total average as the
	//   average value argument for the function computeVarFactor, to compute variance-factors
	//   for each part of the data. Use multi-threading to compute variance-factor for each
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument `target_file`.
	// Also, read the workshop instruction.


	int ProcessData::operator()(const std::string& targetFile, double& avg, double& var) {
		// Compute average value
		computeAvgFactor(data, total_items, total_items, avg);

		// Compute variance value
		computeVarFactor(data, total_items, total_items, avg, var);

		// Open the target file for writing in binary mode
		std::ofstream outFile(targetFile, std::ios::binary);
		if (outFile.is_open()) {
			// Write the total number of items
			outFile.write(reinterpret_cast<const char*>(&total_items), sizeof(int));

			// Write the data items
			outFile.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));

			// Close the file
			outFile.close();

			//Return 0 if success
			return 0;
		}
		else {
			std::cerr << "Error opening file: " << targetFile << std::endl;

			//Retuen -1 if error, I mean it is not necessary to return anything, but
			//the given function said to return int so yeah IT IS WHAT IT IS!
			return -1;
		}
	}

}
