/*
 * Conner Brinkley
 * February 1, 2019
 * Comparison function implementation
 *
 * This file contains two comparison functions: one for strings and one for integers.
 * These are used for sorting to determine if a value is less than or equal to another.
 * See stl.cpp, merge.cpp, and quick.cpp for how they are used.
 *
 * */

#include "dllist.h"
#include "volsort.h"
#include <string>


/* Returns true if numeric value of a is less than or equal to b */

bool node_number_compare(const Node <std::string> *a, const Node <std::string> *b) {
	
	if (a->getNumericVal() <= b->getNumericVal()) return true;
	else return false;
}


/* Returns true if string value of a is less than or equal to b */

bool node_string_compare(const Node <std::string> *a, const Node <std::string> *b) {
	
	if (a->getData() <= b->getData()) return true;
	else return false;
}
