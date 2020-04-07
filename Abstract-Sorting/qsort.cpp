/*
 * Conner Brinkley
 * February 6, 2019
 * Qsort implementation
 *
 * Performs the c style function qsort on a given list of data.
 *
 * */

#include "dllist.h"
#include "volsort.h"
#include <cstdlib>
#include <vector>
#include <string>


/* Compares two strings. Returns <0 if a<b, 0 if a==b, and >0 if a>b. */

int strComp(const void* a_, const void* b_) {

	const Node <std::string> *a = *(const Node <std::string> **) a_;
	const Node <std::string> *b = *(const Node <std::string> **) b_;

	if (a->getData() < b->getData()) return -1;
	else if (a->getData() == b->getData()) return 0;
	else return 1;
}


/* Compares two integers. Same as above. */

int intComp(const void* a_, const void *b_) {
	
	const Node <std::string> *a = *(const Node <std::string> **) a_;
	const Node <std::string> *b = *(const Node <std::string> **) b_;

	if (a->getNumericVal() < b->getNumericVal()) return -1;
	else if (a->getNumericVal() == b->getNumericVal()) return 0;
	else return 1;
}


/* Creates a vector of pointers to Nodes, calls qsort on it, and then relinks the Nodes so that they are 
 * sorted. */

void qsort_sort(List <std::string> &l, bool numeric) {
	
	std::vector <Node<std::string> *> nodes;
	nodes = l.createVec();

	if (numeric)   qsort(&nodes[0], nodes.size(), sizeof(Node <std::string> *), intComp);
	else           qsort(&nodes[0], nodes.size(), sizeof(Node <std::string> *), strComp);

	l.sort_relink(nodes);
}
