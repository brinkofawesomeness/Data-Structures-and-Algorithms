/* 
 * Conner Brinkley
 * February 6, 2019
 * Sorting Header File
 *
 * Outlines a sorting program that is supposed to mimic the UNIX sorting tool with various algorithms.
 * See below to find where the following functions are implemented.
 *
 * */

#ifndef SORTING_H
#define SORTING_H

#include "dllist.cpp"
#include <string>


/* Comparison functions used by stl.cpp, merge.cpp, and quick.cpp */

bool node_number_compare(const Node <std::string> *a, const Node <std::string> *b);   // defined in compare.cpp
bool node_string_compare(const Node <std::string> *a, const Node <std::string> *b);   // defined in compare.cpp


/* Sorting functions */

void stl_sort(List <std::string> &l, bool numeric);     // defined in stl.cpp
void qsort_sort(List <std::string> &l, bool numeric);   // defined in qsort.cpp
void merge_sort(List <std::string> &l, bool numeric);   // defined in merge.cpp
void quick_sort(List <std::string> &l, bool numeric);   // defined in quick.cpp


#endif
