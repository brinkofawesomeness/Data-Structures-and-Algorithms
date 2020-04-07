// Conner Brinkley
// November 5, 2018
// CS 302 – Lab 7

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


class Node {
	public:
		int id;
		int backedge;
		bool visited;
		vector <int> edges; // adjacency list
};

class Graph {
	public:
		vector <Node *> nodes;
		void Print(int index);				// prints the solution path
		void Solve(int index, int prev);	// DFS maze solution
};


void Graph::Solve(int index, int prev) {
	
	int i;
	
	// check index's visited field. if true, return
	if (nodes.at(index)->visited == true) return;

	// set index's visited field to true, and set the backedge
	nodes.at(index)->visited = true;
	nodes.at(index)->backedge = prev;

	// if we reach the end, print the path
	if (index == nodes.size()-1) Print(index);

	// then, for all edges, call DFS
	for (i = 0; i < nodes.at(index)->edges.size(); i++) {
		Solve( nodes.at(index)->edges.at(i), index );
	}

	// return
	return;
}

void Graph::Print(int index) {

	int i, j;

	// if we're back at start, print and return
	if (index == 0) {
		cout << "PATH " << index << endl;
		return;
	}	

	// if no backedge, return
	if (index == -1) return;

	// recursively call print
	Print(nodes.at(index)->backedge);
	
	// print out path and return
	cout << "PATH " << index << endl;
	return;
	
	
	/* CODE TO PRINT ADJACENCY LISTS

	// loop through all nodes
	for (i = 0; i < nodes.size(); i++) {
		
		// print out adjacency list at each node
		cout << "Node: " << i << " | ";
		for (j = 0; j < nodes.at(i)->edges.size(); j++) {
			cout << " " << nodes.at(i)->edges.at(j);
		}
		cout << endl;
	}

	*/
}

int main() {

	Graph maze;
	Node *n;
	string ROWS, COLS, WALL;
	int numRows, numCols, numNodes;
	int i, j, k;
	int left, right, up, down;
	vector <int>::iterator it;

	// read in ROW/COL declaration and print it out
	cin >> ROWS >> numRows >> COLS >> numCols;
	cout << "ROWS " << numRows << " COLS " << numCols << endl;

	numNodes = numRows*numCols;

	// create all of the nodes
	for (i = 0; i < numNodes; i++) {
		
		n = new Node;					// assign default vals to node
		n->id = i;						// 
		n->visited = false;				// 
		n->backedge = -1;				//

		left = i - 1;					// calculate all adjacent nodes
		right = i + 1;					// 
		up = i - numCols;				//
		down = i + numCols;				//

		// add nodes to adjacency list
		if (left >= 0 && i % numCols != 0)					// makes sure a node in prev row isn't added to adj list
			n->edges.push_back(left);						//
		if (right < numNodes && i % numCols != numCols-1)	// makes sure a node in next row isn't added to adj list
			n->edges.push_back(right);						//
		if (up >= 0)										// makes sure node is valid
			n->edges.push_back(up);							//
		if (down < numNodes)								// makes sure node is valid
			n->edges.push_back(down);						//

		maze.nodes.push_back(n);		// push node onto graph
	}

	// read in all of the WALL specifications
	while (cin >> WALL) {
	
		// print them out
		cin >> i >> j;
		cout << "WALL " << i << " " << j << endl;

		// remove node i and j from each other's adjacency list
		for (k = 0; k < maze.nodes.size(); k++) {
			
			n = maze.nodes.at(k);

			if (n->id == i) {
				it = find( n->edges.begin(), n->edges.end(), j );
				n->edges.erase(it);
			}
			if (n->id == j) {
				it = find( n->edges.begin(), n->edges.end(), i );
				n->edges.erase(it);
			}
		}
	}

	// use DFS to solve the maze
	maze.Solve(0, -1);

	return 0;
}
