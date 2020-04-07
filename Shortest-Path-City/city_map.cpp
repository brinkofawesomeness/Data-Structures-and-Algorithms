/*	
 * Conner Brinkley
 * November, 13, 2018
 * Lab 8 – Dijkstra's Algorithm
 *
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <list>
#include <map>
#include "city_map.h"
using namespace std;


/* City_Map constructor reads in intersection data, creates Intersection nodes, creates a graph from the nodes, 
 * and then builds adjacency lists that serve as road segments between the intersections. */

City_Map::City_Map() {

	// variables and stuff
	int j, k;
	int aveMax = 0;
	int stMax = 0;
	Intersection *i, *from, *to;
	Road_Segment *rs;
	string intersection;
	vector <vector <Intersection *> > cityVec;
	list <Intersection *>::iterator it;


	// read in all of the lights
	while (getline(cin, intersection)) {
		
		// create new intersection
		i = new Intersection;

		// read in values into i
		sscanf(intersection.c_str(), "%d %d %lf %lf %lf %lf", 
				&(i->street), &(i->avenue), &(i->x), &(i->y), &(i->green[0]), &(i->green[1]));

		// keep track of the highest avenue and street
		if (i->avenue > aveMax) aveMax = i->avenue;
		if (i->street > stMax) stMax = i->street;

		// put the intersection in the city map
		all.push_back(i);
	}

	// initialize 2D vector of Intersections
	cityVec.resize(stMax + 1);
	for (j = 0; j <= stMax; j++) {
		cityVec.at(j).resize(aveMax + 1);
	}
	
	// populate cityVec with intersections
	for (it = all.begin(); it != all.end(); it++) {
		cityVec.at((*it)->street).at((*it)->avenue) = *it;
	}

	// set first and last pointers in City_Map
	first = cityVec.at(0).at(0);
	last = cityVec.at(stMax).at(aveMax);

	// build adjacency lists by looping through cityVec
	for (j = 0; j <= stMax; j++) {
		for (k = 0; k <= aveMax; k++) {
		
			// get current intersection
			from = cityVec.at(j).at(k);

			// if ave is a 2-way, or ave is even
			if ( (from->avenue % 5 == 0 || from->avenue == aveMax) || (from->avenue % 2 == 0 && j < stMax) ) {
				
				// look up
				if (j < stMax) {
					
					// get next intersection
					to = cityVec.at(j + 1).at(k);
				
					// create road segment
					rs = new Road_Segment;
					rs->type = AVENUE;
					rs->number = k;
					rs->distance = sqrt(pow(abs(from->x - to->x), 2) + pow(abs(from->y - to->y), 2));
					rs->from = from;
					rs->to = to;

					// add road segment to adjacency list
					from->adj.push_back(rs);
				}
			}
			
			// if ave is a 2-way, or ave is odd
			if ( (from->avenue % 5 == 0 || from->avenue == aveMax) || (from->avenue % 2 != 0 && j != 0)) {
				
				// look down
				if (j != 0) {
					
					// get next intersection
					to = cityVec.at(j - 1).at(k);

					// create road segment
					rs = new Road_Segment;
					rs->type = AVENUE;
					rs->number = k;
					rs->distance = sqrt(pow(abs(from->x - to->x), 2) + pow(abs(from->y - to->y), 2));
					rs->from = from;
					rs->to = to;

					// add road segment to adjacency list
					from->adj.push_back(rs);
				}
			}
			
			// if st. is a 2-way, or st. is even
			if ( (from->street % 5 == 0) || (from->street % 2 == 0 && k < aveMax) ) {
				
				// look left
				if (k < aveMax) {
					
					// get next intersection
					to = cityVec.at(j).at(k + 1);
				
					// create road segment
					rs = new Road_Segment;
					rs->type = STREET;
					rs->number = j;
					rs->distance = sqrt(pow(abs(from->x - to->x), 2) + pow(abs(from->y - to->y), 2));
					rs->from = from;
					rs->to = to;

					// add road segment to adjacency list
					from->adj.push_back(rs);
				}
			}
			
			// if st. is a 2-way, or st. is odd
			if ( (from->street % 5 == 0) || (from->street % 2 != 0 && k != 0) ) {
				
				// look right
				if (k != 0) {
					
					// get next intersection
					to = cityVec.at(j).at(k - 1);
				
					// create road segment
					rs = new Road_Segment;
					rs->type = STREET;
					rs->number = k;
					rs->distance = sqrt(pow(abs(from->x - to->x), 2) + pow(abs(from->y - to->y), 2));
					rs->from = from;
					rs->to = to;

					// add road segment to adjacency list
					from->adj.push_back(rs);
				}
			}
		}
	}
}


/* Dijkstra's algorithm does a breadth first search on the graph, accounting for the weighted edges (time to travel 
 * from one intersection to the next). When it is done, the function crawls the backedges until it reaches node 0, 
 * and it calculates total time to get from first to last in the best, worst, and average cases (depending on time 
 * spend waiting at traffic lights). */

double City_Map::Dijkstra(int avg_best_worst) {
	
	// variables and stuff
	double time, totalTime;
	Intersection *i;
	list <Intersection *>::iterator it;
	list <class Road_Segment *>::iterator eit;
	multimap <double, Intersection *>::iterator mmit;


	// set all nodes' backedges to NULL and best times to -1
	for (it = all.begin(); it != all.end(); it++) {
		(*it)->backedge = NULL;
		(*it)->best_time = -1;
	}

	// set node 0's best time to 0 and put it on the multimap
	first->best_time = 0.0;
	bfsq.insert( pair<double, Intersection *>(first->best_time, first) );


	// repeat until there are no more nodes to process
	while (!bfsq.empty()) {
	
		// remove a node from the front of the multimap
		i = bfsq.begin()->second;
		bfsq.erase( bfsq.begin() );

		// loop through the adjacency list
		for (eit = i->adj.begin(); eit != i->adj.end(); eit++) {
		
			// calculate time waiting at lights
			time = 0.0;
			switch(avg_best_worst) {

				// avg case (using equation given in lab write-up)
				case 'A': if ((*eit)->type == AVENUE) {
							time = ((*eit)->to->green[0] * (*eit)->to->green[0]) / (2 * ((*eit)->to->green[0] + (*eit)->to->green[1]));
						  } 
						  else if ((*eit)->type == STREET) {
							time = ((*eit)->to->green[1] * (*eit)->to->green[1]) / (2 * ((*eit)->to->green[0] + (*eit)->to->green[1]));
						  }
						  break;

				// worst case (we arrive at the light immediately when it turns red)
				case 'W': if ((*eit)->type == AVENUE) {
							time = (*eit)->to->green[0];
						  }
						  else if ((*eit)->type == STREET) {
							time = (*eit)->to->green[1];
						  }
						  break;

				// best case (continue with algorithm)
				case 'B': break;
			} 
			
			// calculate seconds to travel road segment at 30 mph, after accounting for light times (optional), 
			// and add that to intersection's best time
			time += ( ((*eit)->distance / 30) * 3600 ) + i->best_time;
			
			// if *to best time is -1, or if time (calculated above) is less than current best time
			if ( (*eit)->to->best_time == -1 || (*eit)->to->best_time > time ) {
				
				// set *to best time to time
				(*eit)->to->best_time = time;

				// set *to backedge to eit
				(*eit)->to->backedge = *eit;

				// insert node into multimap, keyed on best time
				bfsq.insert( pair<double, Intersection *>(time, (*eit)->to) );

				// set bfsq pointer so we can erase later
				for (mmit = bfsq.begin(); mmit != bfsq.end(); mmit++) {
					if (mmit->second == (*eit)->to) {
						(*eit)->to->bfsq_ptr = mmit;
					}
				}
			}
		}
	}
	
	// traverse backedges from *last and create path
	i = last;
	while (i->backedge != NULL) {
		path.push_front(i->backedge);
		i = i->backedge->from;
	}

	// loop through path and calculate totalTime
	totalTime = 0.0;
	for (eit = path.begin(); eit != path.end(); eit++) {
		totalTime += (*eit)->to->best_time;
	}

	return totalTime;
}
