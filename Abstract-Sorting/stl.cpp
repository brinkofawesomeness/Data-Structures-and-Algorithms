/*
 * Conner Brinkley
 * February 6, 2019
 * STL sort implementation
 *
 * Performs STL sort on a given list of data.
 *
 * */

#include "dllist.h"
#include "volsort.h"
#include <algorithm>
#include <vector>
#include <string>


/* Creates a vector of pointers to Nodes, calls STL sort on the vector, and then relinks the Nodes
 * so that they are sorted. */

void stl_sort(List <std::string> &l, bool numeric) {
	
	std::vector <Node<std::string> *> nodes;
	nodes = l.createVec();

	if (numeric)   std::sort (nodes.begin(), nodes.end(), node_number_compare);
	else           std::sort (nodes.begin(), nodes.end(), node_string_compare);
	
	l.sort_relink(nodes);
}
