/*
 *  Conner Brinkley
 *  March 14, 2019
 *  Challenge 07 -- Minimum Spanning Tree
 *
 *  INPUT:  An adjacency matrix with distances to each edge in an undirected graph.
 *  OUTPUT: Edges in alphabetical order that make up the minimum spanning tree and its total edge weight.
 *
 * */

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>


/* Node, Edge, and Graph objects */

class Node {
	public:
		char ID;                             // ID of node
		bool inMST;                          // True if node is in the current spanning tree
		std::vector <class Edge *> adj;      // Adjacency list
};

class Edge {
	public:
		int weight;                          // Weight
		Node *from;                          // Pointer to first vertex
		Node *to;                            // Pointer to next vertex
};

class Graph {
	public:
		Graph(int);                          // Constructor
		~Graph();                            // Destructor
		void Prim();                         // Prim's algorithm for finding the minimum spanning tree
		void printMST();                     // Prints out the minimum spanning tree
		std::vector <Node *> nodes;          // All the nodes in the graph
		std::multiset <std::string> MST;     // Current spanning tree
		std::multimap <int, Edge *> queue;   // Queue used in Prim's: key = weight, value = edge
};


/* Driver code */

int main() {

	Graph *graph;
	int numVertices;
	bool first = true;

	/* Read in graph, format output, run Prim's algorithm, print out MST, and delete the graph */

	while (std::cin >> numVertices) {
		graph = new Graph(numVertices);

		if (!first) std::cout << std::endl;
		first = false;
		
		graph->Prim();
		graph->printMST();
		delete graph;
	}

	return 0;
}


/* Constructor reads in data from standard in and creates the graph accordingly */

Graph::Graph(int numVertices) {
	
	int i;
	int row, col;
	int weight;
	Node *node;
	Edge *edge;

	/* Create nodes */

	for (i = 0; i < numVertices; i++) {
		node = new Node;
		node->ID = i + 'A';
		node->inMST = false;
		nodes.push_back(node);
	}

	/* Read in distance matrix */

	for (row = 0; row < numVertices; row++) {
		for (col = 0; col < numVertices; col++) {

			std::cin >> weight;
			if (weight != -1) {
				edge = new Edge;
				edge->weight = weight;
				edge->from = nodes[col];
				edge->to = nodes[row];

				nodes[col]->adj.push_back(edge);
			}
		}
	}
}


/* Destructor frees up memory in graph before the graph itself is deleted */

Graph::~Graph() {

	unsigned int i, j;

	/* Delete each edge before deleting the node */

	for (i = 0; i < nodes.size(); i++) {
		for (j = 0; j < nodes[i]->adj.size(); j++) {
			delete nodes[i]->adj[j];
		}
		delete nodes[i];
	}
}


/* Runs Prim's algorithm on the graph */

void Graph::Prim() {

	int weight;
	unsigned int i;
	bool updated;
	std::string key;
	Node *start;
	Edge *curr;
	std::multimap <int, Edge *>::iterator it;

	/* Initialize the queue */

	weight = 0;
	start = nodes[0];
	start->inMST = true;
	
	for (i = 0; i < start->adj.size(); i++) {
		queue.insert( std::pair <int, Edge *>( start->adj[i]->weight, start->adj[i] ));
	}

	/* From Dr. Plank's notes */

	while (!queue.empty()) {
	
		/* Reading from queue */ 

		curr = queue.begin()->second;
		curr->to->inMST = true;
		queue.erase( queue.begin() );
		weight += curr->weight;

		/* Inserting into MST */

		key = "";
		if (curr->from->ID < curr->to->ID) {
			key.push_back(curr->from->ID);
			key.push_back(curr->to->ID);
		} else {
			key.push_back(curr->to->ID);
			key.push_back(curr->from->ID);
		}
		MST.insert(key);
	
		/* Going through adjacency list */

		for (i = 0; i < curr->to->adj.size(); i++) {

			if (curr->to->adj[i]->to->inMST == false) {
				updated = false;
				for (it = queue.begin(); it != queue.end(); it++) {

					/* Checking to see if node is already in queue, and updating if it is */

					if (it->second->to->ID == curr->to->adj[i]->to->ID) {
						if (it->second->weight > curr->to->adj[i]->weight) {
							queue.erase(it);
							queue.insert( std::pair <int, Edge *>( curr->to->adj[i]->weight, curr->to->adj[i] ));
						}
						updated = true;
						break;
					}
				}

				/* If it's not already in the queue, insert it */

				if (!updated) {
					queue.insert( std::pair <int, Edge *>( curr->to->adj[i]->weight, curr->to->adj[i] ));
				}
			}
		}
	}
	
	std::cout << weight << std::endl;
}


/* Prints the edges included in the minimum spanning tree */

void Graph::printMST() {
	
	std::multiset <std::string>::iterator it;

	for (it = MST.begin(); it != MST.end(); it++) {
		std::cout << *it << std::endl;
	}
}
