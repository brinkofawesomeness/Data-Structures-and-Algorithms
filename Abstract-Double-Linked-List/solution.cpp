/* 
 * Conner Brinkley
 * February 1, 2019
 * Challenge 02 -- Adding list-based integers
 *
 * INPUT:  Two integers from standard in: they can be arbitrarily long.
 * OUTPUT: The sum of the two integers in standard out.
 *
 * */

#include "dllist.h"
#include <iostream>
#include <string>
using namespace std;

typedef List <int> intList;


/* sum() takes two lists by reference to save memory, and it returns a pointer 
 * to a list holding the sum of the arguments. It is implemented using an 
 * overloaded += operator, which you can find in dllist.cpp */

intList* sum( intList& integer1, intList& integer2 ) {
	
	intList *ll;

	integer1 += integer2;
	ll = &integer1;

	return ll;
}


int main() {

	/* Variable declarations */

	int i;
	intList *ll;
	intList integer1;
	intList integer2;
	string input1, input2;

	/* Keep running until we exit */

	while (cin >> input1 >> input2) {

		/* Loop through the characters of the strings and create lists out of them */
		
		integer1.clear();
		for (i=input1.size()-1; i>=0; i--) {
			integer1.push_back( input1[i] - '0' );
		}

		integer2.clear();
		for (i=input2.size()-1; i>=0; i--) {
			integer2.push_back( input2[i] - '0' );
		}

		/* Call sum() and print it out. Clear the strings before reading in again */

		ll = sum( integer1, integer2 );
		ll->printList();

		input1.clear();
		input2.clear();
	}

	return 0;
}
