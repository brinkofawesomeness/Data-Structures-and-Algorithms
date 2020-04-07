/*
 * Conner Brinkley
 * April 4, 2019
 * Quicksort implementation
 *
 * Performs a custom implementation of quicksort on a given List of data.
 *
 * */

#include "dllist.h"
#include "volsort.h"
#include <string>
#include <iostream>


/* Typedef defines custom comparison function as a parameter. */

typedef bool (*CompareFunction)(const Node <std::string> *a, const Node <std::string> *b);


/* Helper function prototypes. */

Node <std::string> *qsort(Node <std::string> *sent, Node <std::string> *head, CompareFunction compare);
Node <std::string> *concatenate(Node <std::string> *sent, Node <std::string> *left, Node <std::string> *right);
void partition(Node <std::string> *sent, Node <std::string> *head, Node <std::string> *pivot, Node <std::string> *&left, Node <std::string> *&right, CompareFunction compare);


/* Sets the sentinel and head nodes before calling qsort, and then relinks the sentinel to the list. */

void quick_sort(List <std::string> &l, bool numeric) {

	Node <std::string> *sent, *n;
	sent = l.getSentinel();
	n = l.getFirstNode();

	if (numeric)   n = qsort(sent, n, node_number_compare);
	else           n = qsort(sent, n, node_string_compare);

	sent->setNext(n);
}


/* Recursive implementation of quicksort. */

Node <std::string> *qsort(Node <std::string> *sent, Node <std::string> *head, CompareFunction compare) {

	/* Base case: there are 0 or 1 nodes */

	if (head == sent) return head;
	if (head->getNext() == sent) return head;

	/* Set the pivot */

	Node <std::string> *pivot;
	pivot = head;

	/* Partition the list, and sort each half */

	Node <std::string> *left, *right;
	partition(sent, head, pivot, left, right, compare); 
	left = qsort(sent, left, compare);
	right = qsort(sent, right, compare);

	/* Combine the partitions */

	Node <std::string> *newHead;
	newHead = concatenate(sent, left, right);

	return newHead;
}


/* Combines the left and right sublists and returns the head of the new list. */

Node <std::string> *concatenate(Node <std::string> *sent, Node <std::string> *left, Node <std::string> *right) {
	return left;
}


/* Splits the list into two partitions where every value <= pivot comes before it, and everything > pivot comes after. */

void partition(Node <std::string> *sent, Node <std::string> *head, Node <std::string> *pivot, Node <std::string> *&left, Node <std::string> *&right, CompareFunction compare) {

}
