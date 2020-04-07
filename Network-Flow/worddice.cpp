/*
 * Conner Brinkley
 * December 3, 2018
 * Lab A – Network Flow
 *
 */

#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <list>
using namespace std;


typedef enum { SOURCE, SINK, DICE, WORD } Node_Type;

class Node {
	public:
		Node_Type type;				// defines the node
		int id;						// number of node
		bool visited;				// used in BFS()
		vector <bool> letters;		// vector of len 26: letters[i] = true if letter exists
		vector <class Edge *> adj;	// adjacency list
		class Edge *backedge;		// used in BFS()
};

class Edge {
	public:
		Node *to;
		Node *from;
		Edge *reverse;				// same edge, except *to and *from are switched
		int original;				// used in canSpell() to determine flow
		int residual;				// used in canSpell() to determine flow
};

class Graph {
	public:
		vector <Node *> nodes;
		vector <int> solutionIds;		// used to print
		int minNodes;					// used in deleteHalfGraph() to resize nodes to minNodes
		int BFS();						// performs breadth first search on graph
		int canSpell();					// calls BFS(): returns 1 if word can be spelled, else 0
		void createEdge(Node*, Node*);	// creates Edge between two Nodes
		void deleteHalfGraph();			// deletes WORD nodes and SINK
		void printGraph();				// used for testing
};


int Graph::BFS() {

	int i;
	Node *currNode;
	list <Node *> Q;

	// loop through all nodes and make sure backedges == NULL and visited == false
	for (i = 0; i < nodes.size(); i++) {
		nodes.at(i)->backedge = NULL;
		nodes.at(i)->visited = false;
	}

	// push SOURCE onto queue
	currNode = nodes.at(0);
	currNode->visited = true;
	Q.push_back(currNode);

	// keep looping through while there are more nodes to process
	while ( !Q.empty() ) {

		// remove node from queue
		currNode = *Q.begin();
		Q.pop_front();

		// for each edge in currNode's adjacency list
		for (i = 0; i < currNode->adj.size(); i++) {
			
			// executes if edge's original is 1, and the node has not been visited
			if (currNode->adj.at(i)->original == 1 && !currNode->adj.at(i)->to->visited) {
				
				// set visited to true, set backedge, then push onto queue
				currNode->adj.at(i)->to->visited = true;
				currNode->adj.at(i)->to->backedge = currNode->adj.at(i);
				Q.push_back( currNode->adj.at(i)->to );
			}
		}
	}

	// if we visited the SINK, we found a path
	if ( nodes.at( nodes.size()-1 )->visited ) return 1;
	else return 0;
}

int Graph::canSpell() {
	
	int i;
	Node *currNode;

	// keep looping until BFS can't find any more paths 
	while (BFS()) {

		// start at the SINK
		currNode = nodes.at( nodes.size() - 1 );

		// follow backedges from SINK to SOURCE
		while (currNode->type != SOURCE) {
	
			// if we're at the WORD node, add the corresponding DICE node to the solution vector
			if (currNode->type == WORD) {
				solutionIds.at( currNode->id - minNodes ) = currNode->backedge->from->id - 1;
			}

			// update original and residual values for each edge (this ensures BFS won't follow same path twice)
			currNode->backedge->original = 0;
			currNode->backedge->residual = 1;

			currNode->backedge->reverse->original = 1;
			currNode->backedge->reverse->residual = 0;

			// traverse back a node
			currNode = currNode->backedge->from;
		}
	}

	// loop through all WORD nodes, if any residual edge does not equal 1, then you can't spell the word
	for (i = minNodes; i < nodes.size()-1; i++) {
		if (nodes.at(i)->adj.at(0)->residual != 1) return 0;
	}

	// if we've made it this far, you can spell the word
	return 1;
}

void Graph::createEdge(Node *from, Node *to) {

	// create new Edge
	Edge *edge;
	edge = new Edge;
	edge->to = to;
	edge->from = from;
	edge->original = 1;
	edge->residual = 0;
	
	// create reverse edge
	edge->reverse = new Edge;
	edge->reverse->to = from;
	edge->reverse->from = to;
	edge->reverse->original = 0;
	edge->reverse->residual = 1;
	edge->reverse->reverse = edge;

	// update *from and *to node's adjacency list
	from->adj.push_back(edge);
	to->adj.push_back(edge->reverse);
}

void Graph::deleteHalfGraph() {

	// iterators
	int i, j, k;
	Node *currNode, *source;

	// delete the SINK
	delete nodes.at( nodes.size()-1 );

	// loop through all DICE nodes
	for (i = 1; i < minNodes; i++) {
		
		// set current node
		currNode = nodes.at(i);

		// loop through adjacency list and remove all edges that go to WORD nodes
		for (j = 0; j < currNode->adj.size(); j++) {
			currNode->adj.resize(1);
		}
	}

	// loop through all WORD nodes
	for (i = minNodes; i < nodes.size()-1; i++) {
		
		// loop through adjacency list and delete all edges
		for (j = 0; j < nodes.at(i)->adj.size(); j++) {
			delete nodes.at(i)->adj.at(j);
		}

		// then delete the node
		delete nodes.at(i);
	}

	// resize graph to minNodes
	nodes.resize(minNodes);

	// loop through and reset all original and residual values in each edge
	source = nodes.at(0);
	for (i = 0; i < source->adj.size(); i++) {
		source->adj.at(i)->original = 1;
		source->adj.at(i)->residual = 0;

		source->adj.at(i)->reverse->original = 0;
		source->adj.at(i)->reverse->residual = 1;
	}

	// reset solution vector
	solutionIds.resize(0);
}


int main(int argc, char *argv[]) {
	
	// vars and stuff
	int i, j;
	Node *source, *sink;
	Node *dice, *word;
	Node *currNode;
	Edge *edge;
	Graph *graph;
	string line;

	// create source node
	source = new Node;
	source->type = SOURCE;
	source->id = 0;

	// create graph
	graph = new Graph;
	graph->nodes.push_back(source);
	graph->minNodes = 1;

	// open files
	ifstream diceFile(argv[1]);
	ifstream wordList(argv[2]);

	// read in diceFile
	while ( getline(diceFile, line) ) {
		
		// create new DICE node
		dice = new Node;
		dice->type = DICE;
		dice->id = graph->minNodes;
		dice->letters.resize(26, false);
		for (i = 0; i < line.size(); i++) {
			dice->letters.at( line[i] - 'A' ) = true;
		}

		// create new Edge from SOURCE to DICE node
		graph->createEdge( source, dice );

		// add to graph, and update number of nodes
		graph->nodes.push_back(dice);
		graph->minNodes++;
	}

	// read in wordList
	while ( getline(wordList, line) ) {
	
		// create SINK node
		sink = new Node;
		sink->type = SINK;
		sink->id = graph->nodes.size() + line.size();

		// create a new WORD node for each letter in the word
		for (i = 0; i < line.size(); i++) {
			
			word = new Node;
			word->type = WORD;
			word->id = graph->nodes.size();
			word->letters.resize(26, false);
			word->letters.at( line[i] - 'A' ) = true;

			// create an edge from each WORD to the SINK
			graph->createEdge( word, sink );

			// add WORD node to Graph and resize solution vector
			graph->nodes.push_back(word);
			graph->solutionIds.resize( line.size() );

			// loop through DICE nodes and create Edges to WORD nodes
			for (j = 1; j < graph->minNodes; j++) {
				
				// set current DICE node
				currNode = graph->nodes.at(j);

				// if the current letter is in the DICE node, create an Edge
				if (currNode->letters.at( line[i] - 'A' )) {
					graph->createEdge( currNode, word );
				}
			}
		}

		// add SINK node to Graph
		graph->nodes.push_back(sink);

		// if canSpell() returns 0
		if ( !graph->canSpell() ) {
			printf("Cannot spell %s\n", line.c_str());
		}

		// else, it can spell the word
		else {
			for (i = 0; i < graph->solutionIds.size(); i++) {
				printf("%i", graph->solutionIds.at(i));
				if (i != graph->solutionIds.size()-1) printf(",");
			}
			printf(": %s\n", line.c_str());
		}

		// delete WORD and SINK nodes before next iteration
		graph->deleteHalfGraph();
	}

	// delete all the remaining edges
	for (i = 0; i < graph->nodes.at(0)->adj.size(); i++) {
		delete graph->nodes.at(0)->adj.at(i);
	}

	// delete all the nodes
	for (i = 0; i < graph->nodes.size(); i++) {
		delete graph->nodes.at(i);
	}

	// delete the graph
	delete graph;

	// close the files
	diceFile.close();
	wordList.close();

	return 0;
}
