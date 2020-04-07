/*
 * Conner Brinkley
 * February 16, 2019
 * CS 302 Challenge 04 -- driver code
 *
 * */

#include "heap.h"
#include <iostream>
#include <sstream>
#include <vector>


bool isMaxHeap(std::vector <int> &);


int main() {
	
	Heap *heap;                // Min heap
	int size, k, num;          // Size of data, kth number, number for parsing 
	std::string line, numbers; // Strings for parsing data
	std::stringstream buffer;  // Stringstream for parsing input
	std::vector <int> input;   // Vector to hold data from input

	while (getline(std::cin, line)) {
		
		/* Clear everything and read in initial line. */

		buffer.str(line);
		buffer >> size >> k;
		buffer.clear();
		input.clear();
			
		getline(std::cin, numbers);
		
		/* Parse the data string and create a new heap. */

		heap = new Heap;
		buffer.str(numbers);
		while (buffer >> num) {
			input.push_back(num);
			heap->Push(num);
		}
		buffer.clear();

		/* Get rid of all the numbers before the kth smallest number. */

		while (k != 1) {
			heap->Pop();
			k--;
		}

		/* Print out whether it was a max heap and then the kth smallest number. */

		std::cout << ((isMaxHeap(input)) ? "Y  " : "N  ");
		std::cout << heap->Pop() << std::endl;

		delete heap;
	}

	return 0;
}


/* Checks whether input data was a max heap by starting at the last element and checking 
 * to see if its parent is smaller. It iteratively does this up to the root and returns 
 * true if none of the elements violate the max heap condition. */

bool isMaxHeap(std::vector <int> &input) {
	
	int index = input.size()-1;
	int parent = (index - 1) / 2;

	while (index != 0) {
		if (input.at(parent) < input.at(index)) { 
			return false;
		}
		index--;
		parent = (index - 1) / 2;
	}

	return true;
}
