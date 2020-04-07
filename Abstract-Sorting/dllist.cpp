/* 
 * Conner Brinkley
 * February 1, 2019
 * Linked-List Implementation
 *
 * Contains implementations of the Node and List classes found in dllist.h.
 * Refer to dllist.h for an overview.
 *
 * */

#include "dllist.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>


/* Constructor for Node class, which uses an initialization list */

template <typename T>
Node <T>::Node (const T &val) : data(val), numericVal( atoi(val.c_str()) ), next(NULL), prev(NULL) {}


/* Simply returns the data held by the Node */

template <typename T>
T Node <T>::getData() const { 
	
	return data; 
}


/* Simply returns the numeric value of the data (if applicable) */

template <typename T>
int Node <T>::getNumericVal() const {
	
	return numericVal;
}


/* Returns a pointer to the next Node */

template <typename T>
Node <T>* Node <T>::getNext() const {
	
	return next;
}


/* Returns a pointer to the previous Node */

template <typename T>
Node <T>* Node <T>::getPrev() const {
	
	return prev;
}


/* Sets the Node's next pointer */

template <typename T>
void Node <T>::setNext(Node <T> *ptr) {

	this->next = ptr;
}


/* Sets the Node's prev pointer */

template <typename T>
void Node <T>::setPrev(Node <T> *ptr) {
	
	this->prev = ptr;
}


/* Constructor for List class, which uses an initialization list */

template <typename T>
List <T>::List() : size(0), sentinel( newNode("") ) {}


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


/* Returns a pointer to the first Node in the List */

template <typename T>
Node <T>* List <T>::getFirstNode() {
	
	return sentinel->next;
}


/* Returns a pointer to the sentinel */

template <typename T>
Node <T>* List <T>::getSentinel() {
	
	return sentinel;
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


/* Iterates through and prints out the List. Typically used for testing */

template <typename T>
void List <T>::printList(bool numeric) {
	
	Node <T> *n;
	n = sentinel->next;

	while (n != sentinel) {
		if (numeric)  std::cout << n->getNumericVal() << std::endl;
		else          std::cout << n->getData() << std::endl;
		n = n->next;
	}
}


/* Creates a new Node and relinks the pointers so it is added
 * to the front of the List. The size is incremented after it's 
 * added */

template <typename T>
void List <T>::push_front(const T &val) {
	
	Node <T> *n;
	n = newNode(val);

	if (isEmpty()) {
		sentinel->next = sentinel;
		sentinel->prev = sentinel;
	}

	n->next = sentinel->next;
	n->prev = sentinel;

	n->next->prev = n;
	sentinel->next = n;

	size++;
}


/* Same as push_front, except it adds the Node to the end of the 
 * List */ 

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


/* Relinks the list in sorted order using a sorted vector of Node 
 * pointers */

template <typename T>
void List <T>::sort_relink(std::vector <Node<T> *> &vec) {

	Node <T> *prev;
	typename std::vector <Node<T> *>::iterator it;
	
	prev = sentinel;
	it = vec.begin();

	for (; it != vec.end(); it++) {
		
		prev->next = *it;
		(*it)->prev = prev;
		
		prev = *it;
	}

	prev->next = sentinel;
	sentinel->prev = prev;
}


/* Creates a vector, loops through the List, and pushes back a 
 * pointer to each Node on the vector */

template <typename T>
std::vector <Node<T> *> List <T>::createVec() {
	
	Node <T> *n = sentinel->next;
	std::vector <Node<T> *> nodes;

	while (n != sentinel) {
		nodes.push_back(n);
		n = n->next;
	}

	return nodes;
}


/* Simply creates a new Node and returns a pointer to it */

template <typename T>
Node <T> *List <T>::newNode(const T &val) {
	
	Node <T> *n;
	n = new Node <T> (val);
	
	return n;
}


/* Explicit instantiation to avoid linking errors */

template class List <std::string>;
