/* 
 * Conner Brinkley
 * February 1, 2019
 * Linked-List Header File
 *
 * Refer to dllist.cpp for the class implementations.
 *
 * */

#ifndef LIST_H
#define LIST_H

template <typename T> class List;  // forward declaration of List for Node class

template <typename T>
class Node {

	friend class List <T>;      // allows List access to private variables

	public:
		Node(const T &);        // constructor that initializes data
		T getData() const;      // getter: returns data
	private:
		T data;                 // data stored in the node
		Node <T> *next;         // pointer to next node
		Node <T> *prev;         // pointer to previous node
};

template <typename T>
class List {
	public:
		List();                                      // constructor for linked list
		List(const List <T>& original);              // copy constructor
		~List();                                     // destructor for linked list
		const int isEmpty();                         // checks if list is empty
		int getSize();                               // returns size
		void clear();                                // clears the list (except for sentinel)
		void printList();                            // prints out the list
		void push_back(const T &);                   // adds new node at end of list
		List <T>* operator += (List <T>& rhs);       // overloading += operator
	private:
		int size;                       // keeps track of size
		Node <T> *sentinel;             // sentinel node
		Node <T> *newNode(const T &);   // used to create new nodes
};

#endif
