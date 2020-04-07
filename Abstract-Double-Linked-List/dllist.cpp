/* 
 * Conner Brinkley
 * February 1, 2019
 * Linked-List Implementation
 *
 * Refer to dllist.h for the class declarations.
 *
 * */

#include "dllist.h"
#include <iostream>
#include <string>
using namespace std;


/* Constructor for Node class, which uses an initialization list */

template <typename T>
Node <T>::Node (const T &val) : data(val), next(NULL), prev(NULL) {}


/* Simply returns the data held by the Node */

template <typename T>
T Node <T>::getData() const { 
	
	return data; 
}


/* Constructor for List class, which uses an initialization list */

template <typename T>
List <T>::List() : size(0), sentinel( newNode(0) ) {}


/* Copy constructor for the List class. Loops through original List
 * and pushes back all of its values to new List */

template <typename T>
List <T>::List(const List <T>& original) {
	
	Node <T> *n;
	n = original.sentinel->next;

	this->clear();
	
	while (n != original.sentinel) {
		this->push_back( n->data );
		n = n->next;
	}
}


/* Destructor for List class. Iterates through entire List and 
 * frees up memory */

template <typename T>
List <T>::~List() {
	
	if (!isEmpty()) {
		Node <T> *n, *next;
		n = sentinel->next;

		while (n != sentinel) {
			next = n->next;
			delete n;
			n = next;
			size--;
		}
	}

	delete sentinel;
}


/* Simply checks if the List is empty. It ignores the sentinel Node */

template <typename T>
const int List <T>::isEmpty() {
	
	if (size == 0) return 1;
	else return 0;
}


/* Simply returns the size of the List */

template <typename T>
int List <T>::getSize() {
	
	return size;
}


/* Deletes every Node in the List and decrements the size. It 
 * ignores the sentinel Node */

template <typename T>
void List <T>::clear() {
	
	if (!isEmpty()) {
		Node <T> *n, *next;
		n = sentinel->next;

		while (n != sentinel) {
			next = n->next;
			delete n;
			n = next;
			size--;
		}
	}
}


/* Iterates through and prints out the List in reverse order.
 * This is because the numbers are stored in reverse order to 
 * make adding and carrying remainders easier */

template <typename T>
void List <T>::printList() {
	
	Node <T> *n;
	n = sentinel->prev;

	while (n != sentinel) {
		cout << n->getData();
		n = n->prev;
	}
	
	cout << endl;
}


/* Creates a new Node and relinks the pointers so it is added 
 * to the List. The size is incremented after it's added */

template <typename T>
void List <T>::push_back(const T &val) {

	Node <T> *n;
	n = newNode(val);

	if (isEmpty()) {
		sentinel->next = sentinel;
		sentinel->prev = sentinel;
	}

	n->next = sentinel;
	n->prev = sentinel->prev;

	n->prev->next = n;
	sentinel->prev = n;

	size++;
}


/* Overloaded += operator to make adding integers easier in solution.cpp */

template <typename T>
List <T>* List <T>::operator += (List <T>& rhs) {

	/* Variable declarations */

	int diff;
	int i;
	Node <T> *n1, *n2;

	/* Find the difference in size (if any) */

	diff = this->size - rhs.size;
	if (diff < 0) diff = -diff;

	/* Make the two Lists equal in size by pushing back 0's on the smaller one */

	for (i = 0; i < diff; i++) { 
		
		(this->size < rhs.size) ? this->push_back(0) : rhs.push_back(0);
	}
	
	/* Simultaneously loop through the first and second List and add each of 
	 * their Node values together to produce the sum, and store it in the first 
	 * List */

	n1 = this->sentinel->next;
	n2 = rhs.sentinel->next;

	while (n1 != this->sentinel) {	
		n1->data = n1->data + n2->data;
		
		/* This handles remainders when the sum is greater than 9 by adding 1 to 
		 * the next Node */

		if (n1->data > 9) {	
			n1->data -= 10;
			
			if (n1->next == this->sentinel) {
				this->push_back(1);
			} 
			else { 
				n1->next->data += 1; 
			}
		}

		/* Increment */

		n1 = n1->next;
		n2 = n2->next;
	}

	return this;	
}


/* Simply creates a new Node and returns a pointer to it */

template <typename T>
Node <T> *List <T>::newNode(const T &val) {
	
	Node <T> *n;
	n = new Node <T> (val);
	
	return n;
}


/* Explicit instantiation to avoid linking errors */

template class List <int>;
