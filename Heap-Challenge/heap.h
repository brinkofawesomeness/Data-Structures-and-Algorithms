/*
 * Conner Brinkley
 * February 16, 2019
 * Heap class header file
 *
 * */

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>


class Heap {
	public:
		Heap();                          // Constructor
		Heap(const Heap &init);          // Copy constructor
		~Heap();                         // Destructor
		void Push(int num);              // Adds an element to min heap
		int Pop();                       // Removes min element from heap
		int Size();                      // Returns min heap size
		bool Empty();                    // Checks if min heap is empty
		void Print();                    // Prints min heap
	private:
		std::vector <int> numbers;       // Min heap
		void Percolate_Up(int index);    // Used in Push()
		void Percolate_Down(int index);  // Used in Pop()
};


#endif
