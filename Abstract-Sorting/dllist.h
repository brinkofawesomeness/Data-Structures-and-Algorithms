/* 
 * Conner Brinkley
 * February 1, 2019
 * Linked-List Header File
 *
 * Defines a Node object and a List of Nodes (doubly linked list).
 * Refer to dllist.cpp for the class implementations.
 *
 * */

#ifndef LIST_H
#define LIST_H

#include <vector>

template <typename T> class List;  // forward declaration of List for Node class

template <typename T>
class Node {

	friend class List <T>;      // allows List access to private variables

	public:
		Node(const T &);                // constructor that initializes data
		T getData() const;              // getter: returns data
		int getNumericVal() const;      // getter: returns numeric value of data
		Node <T> *getNext() const;      // getter: returns a pointer to next node
		Node <T> *getPrev() const;      // getter: returns a pointer to prev node
		void setNext(Node <T> *);       // setter: sets the Node's next pointer
		void setPrev(Node <T> *);       // setter: sets the Node's prev pointer
	private:
		T data;                 // data stored in the node
		int numericVal;         // numeric version of data (if applicable)
		Node <T> *next;         // pointer to next node
		Node <T> *prev;         // pointer to previous node
};

template <typename T>
class List {
	public:
		List();                                      // constructor for linked list
		List(const List <T>& original);              // copy constructor
		~List();                                     // destructor for linked list
		Node <T> *getFirstNode();                    // returns a pointer to the first Node in the list
		Node <T> *getSentinel();                     // returns a pointer to the sentinel
		const int isEmpty();                         // checks if list is empty
		int getSize();                               // returns size
		void clear();                                // clears the list (except for sentinel)
		void printList(bool numeric);                // prints out the list
		void push_front(const T &);                  // adds new node at front of list
		void push_back(const T &);                   // adds new node at end of list
		void sort_relink(std::vector <Node<T> *> &); // relinks the list based on the sorted vector (used in STL sort)
		std::vector <Node<T> *> createVec();         // returns a vector with pointers to each node
	private:
		int size;                       // keeps track of size
		Node <T> *sentinel;             // sentinel node
		Node <T> *newNode(const T &);   // used to create new nodes
};

#endif
