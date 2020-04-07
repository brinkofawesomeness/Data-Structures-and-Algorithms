/*
 * Conner Brinkley
 * April 4, 2019
 * Merge sort implementation
 *
 * Performs a custom implementation of merge sort on a given List of data.
 *
 * */

#include "dllist.h"
#include "volsort.h"
#include <string>
#include <iostream>

/* Typedef defines custom comparison function as a parameter. */

typedef bool (*CompareFunction)(const Node <std::string> *a, const Node <std::string> *b);


/* Helper function prototypes. */

Node <std::string> *msort(Node <std::string> *sent, Node <std::string> *head, CompareFunction compare);
Node <std::string> *merge(Node <std::string> *sent, Node <std::string> *left, Node <std::string> *right, CompareFunction compare);
void split(Node <std::string> *sent, Node <std::string> *head, Node <std::string> *&left, Node <std::string> *&right);


/* Sets the sentinel and head nodes before calling msort, and then relinks the Nodes so that they are sorted. */

void merge_sort(List <std::string> &l, bool numeric) {

	Node <std::string> *sent, *n;
	sent = l.getSentinel();
	n = l.getFirstNode();

	if (numeric)   n = msort(sent, n, node_number_compare);
	else           n = msort(sent, n, node_string_compare);

	sent->setNext(n);
}


/* Recursive implementation of merge sort. */

Node <std::string> *msort(Node <std::string> *sent, Node <std::string> *head, CompareFunction compare) {

	/* Base case: there is only one node or none */

	if (head == sent) return NULL;
	if (head->getNext() == sent) return head;

	/* Divide into left and right sublists */

	Node <std::string> *left, *right;
	split(sent, head, left, right);

	/* Conquer left and right sublists */

	left = msort(sent, left, compare);    
	right = msort(sent, right, compare); 

	/* Merge the two sublists */
	
	Node <std::string> *newHead;
	newHead = merge(sent, left, right, compare);

	return newHead;
}


/* Iteratively merges the left and right sublists into one sorted list. */

Node <std::string> *merge(Node <std::string> *sent, Node <std::string> *left, Node <std::string> *right, CompareFunction compare) {

	Node <std::string> *curr = sent;

	/* Compare and merge the two sublists */

	while (left != sent && right != sent) {
		if (compare(left, right)) {
			curr->setNext(left);
			curr = curr->getNext();
			left = left->getNext();
		} else {
			curr->setNext(right);
			curr = curr->getNext();
			right = right->getNext();
		}
	}

	/* If there are any in the left sublist, add the rest */

	while (left != sent) {
		curr->setNext(left);
		curr = curr->getNext();
		left = left->getNext();
	}

	/* If there are any in the right sublist, add the rest */

	while (right != sent) {
		curr->setNext(right);
		curr = curr->getNext();
		right = right->getNext();
	}

	return sent->getNext();
}


/* Splits the list into two sublists using the slow and fast pointer trick. */

void split(Node <std::string> *sent, Node <std::string> *head, Node <std::string> *&left, Node <std::string> *&right) {

	/* Set tortoise and hare pointers */

	Node <std::string> *tortoise, *hare;
	tortoise = head;
	hare = head->getNext();

	/* For every node tortoise advances, hare advances two */

	while (hare != sent) {
		hare = hare->getNext();
		if (hare != sent) {
			tortoise = tortoise->getNext();
			hare = hare->getNext();
		}
	}

	/* Split the list in half */

	left = head;
	right = tortoise->getNext();
	tortoise->setNext(sent);
}
