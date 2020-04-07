/*
 * Conner Brinkley
 * February 16, 2019
 * Heap class implementation
 *
 * */

#include "heap.h"
#include <iostream>
#include <cstdlib>
#include <vector>


/* Constructor clears the heap. */

Heap::Heap() {
	numbers.clear();
}


/* Copy constructor copies vector to another heap. */

Heap::Heap(const Heap &init) {

	int i;

	this->numbers.clear();

	for (i = 0; i < init.numbers.size(); i++) {
		this->numbers.push_back( init.numbers.at(i) );
	}
}


/* Destructor clears the heap. */

Heap::~Heap() {
	numbers.clear();
}


/* Insert number at the end of the heap and call Percolate_Up on it. */

void Heap::Push(int num) {

	numbers.push_back(num);
	Percolate_Up( numbers.size()-1 );
}


/* Moves last element in heap to the root and calls Percolate_Down. */

int Heap::Pop() {

	int root;

	if (Empty()) {
		std::cerr << "Error: called Pop() on an empty heap\n";
		exit(1);
	}

	root = numbers.at(0);
	numbers.at(0) = numbers.at( numbers.size()-1 );
	numbers.pop_back();

	if (Empty()) return root;
	
	Percolate_Down(0);
	return root;
}


/* Returns the size of the heap vector. */

int Heap::Size() {
	return numbers.size();
}


/* Checks if the data structure is empty. */

bool Heap::Empty() {
	if (numbers.empty()) return true;
	else return false;
}


/* Prints out the heap. */

void Heap::Print() {
	
	int i;

	for (i = 0; i < numbers.size()-1; i++) {
		std::cout << numbers.at(i) << " ";
	}

	std::cout << numbers.at( numbers.size()-1 ) << std::endl;
}


/* Keep swapping the index with its parent while the parent is > the index. */

void Heap::Percolate_Up(int index) {
	
	int	parent = (index-1) / 2;

	while (index != 0 && numbers.at(parent) > numbers.at(index)) {

		/* XOR swap */

		numbers.at(index) = numbers.at(index) ^ numbers.at(parent);
		numbers.at(parent) = numbers.at(index) ^ numbers.at(parent);
		numbers.at(index) = numbers.at(index) ^ numbers.at(parent);
	
		index = parent;
		parent = (index-1) / 2;
	}
}


/* Keep swapping index with one of its children while one of the children is 
 * less than the index. */

void Heap::Percolate_Down(int index) {
	
	int l_child, r_child;

	while (true) {
		
		l_child = index*2 + 1;
		r_child = l_child + 1;

		if (l_child >= numbers.size()) return;

		/* If left child is smaller than index and the right child, XOR swap with index */

		if (r_child == numbers.size() || numbers.at(l_child) <= numbers.at(r_child)) {
			
			if (numbers.at(l_child) < numbers.at(index)) {
				numbers.at(l_child) = numbers.at(l_child) ^ numbers.at(index);
				numbers.at(index) = numbers.at(l_child) ^ numbers.at(index);
				numbers.at(l_child) = numbers.at(l_child) ^ numbers.at(index);

				index = l_child;
			}

			else return;
		}

		/* If right child is smaller, XOR swap with it */

		else if (numbers.at(r_child) < numbers.at(index)) {
			numbers.at(r_child) = numbers.at(r_child) ^ numbers.at(index);
			numbers.at(index) = numbers.at(r_child) ^ numbers.at(index);
			numbers.at(r_child) = numbers.at(r_child) ^ numbers.at(index);
		
			index = r_child;
		}

		else return;
	}
}
