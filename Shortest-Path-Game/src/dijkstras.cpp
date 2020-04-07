/*
 * Conner Brinkley
 * March 15, 2019
 * Project 04 -- Path Finding
 *
 * INPUT:  A game board on standard in.
 * OUTPUT: The quickest path from one tile to a goal tile.
 *
 * */

#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <unordered_map>  // finds tile costs in O(1) time


/* Tile, Path, and Map objects */

class Tile {
	public:
		char type;
		int x, y;                           // coordinates
		int bestCost;
		class Path *backedge;
		std::list <class Path *> adjacent;
};

class Path {
	public:
		int cost;
		Tile *from;
		Tile *to;
};

class Map {
	public:
		Map();
		~Map();
		void Dijkstra();
		void PrintPath();
		Tile *start;
		Tile *goal;
		std::list <Path *> path;                      // holds the shortest path to the goal tile
		std::list <Tile *> allTiles;                  // holds each node in the graph
		std::multimap <int, Tile *> queue;            // queue for BFS
		std::unordered_map <char, int> TILE_TYPES;    // hash table keyed on tile type, with value = cost of tile
		std::unordered_map <char, int>::iterator it;
};


/* Driver code */

int main() {

	Map *game;
	game = new Map;

	game->Dijkstra();
	game->PrintPath();

	delete game;
	return 0;
}


/* Constructor reads data from standard in and creates game map accordingly */

Map::Map() {

	char type;                                  // holds tile type
	int tiles_N;                                // number of different tiles
	int MAP_ROWS, MAP_COLS;                     // number of rows and columns on board
	int cost;
	int i, j;
	Path *path;
	Tile *tile, *from, *to;
	std::vector <std::vector <Tile *> > BOARD;  // makes creating adjacency lists easier
	
	/* Read in different tile types and insert them in hash table */

	std::cin >> tiles_N;
	
	for (i = 0; i < tiles_N; i++) {
		std::cin >> type >> cost;
		TILE_TYPES[type] = cost;
	}

	/* Read in dimensions and resize board vector */

	std::cin >>	MAP_ROWS >> MAP_COLS;

	BOARD.resize(MAP_ROWS);
	for (i = 0; i < MAP_ROWS; i++) {
		BOARD[i].resize(MAP_COLS);
	}
	
	/* Populate the graph and vector with tiles */

	for (i = 0; i < MAP_ROWS; i++) {
		for (j = 0; j < MAP_COLS; j++) {
			
			std::cin >> type;
			
			tile = new Tile;
			tile->type = type;
			tile->x = i;
			tile->y = j;
			
			BOARD[i][j] = tile;
			allTiles.push_back(tile);
		}
	}

	/* Read in start and goal cells */

	std::cin >> i >> j;
	start = BOARD[i][j];

	std::cin >> i >> j;
	goal = BOARD[i][j];

	/* Loop through board vector and build adjacency lists */

	for (i = 0; i < MAP_ROWS; i++) {
		for (j = 0; j < MAP_COLS; j++) {
		
			/* Start with current tile, get type, and find the cost associated with the type */

			from = BOARD[i][j];
			type = from->type;
			it = TILE_TYPES.find(type);
			cost = it->second;

			/* If i is not the first row, look up, create path, calculate cost, and put path in adjacency list */

			if (i != 0) {
				to = BOARD[i-1][j];

				path = new Path;
				path->from = from;
				path->to = to;
                path->cost = cost;

				from->adjacent.push_back(path);
			}

			/* If i is not the last row, look down, and do the same as above */

			if (i != MAP_ROWS-1) {
				to = BOARD[i+1][j];

				path = new Path;
				path->from = from;
				path->to = to;
				path->cost = cost;
			
				from->adjacent.push_back(path);
			}

			/* If j is not the first column, look left, and do the same as above */

			if (j != 0) {
				to = BOARD[i][j-1];

				path = new Path;
				path->from = from;
				path->to = to;
				path->cost = cost;
			
				from->adjacent.push_back(path);
			}

			/* If j is not the last column, look right, and do the same as above */

			if (j != MAP_COLS-1) {
				to = BOARD[i][j+1];

				path = new Path;
				path->from = from;
				path->to = to;
				path->cost = cost;
			
				from->adjacent.push_back(path);
			}
		}
	}
}


/* Deletes every node's adjacency list before deleting each node */

Map::~Map() {

	std::list <Tile *>::iterator tile_it;
	std::list <Path *>::iterator path_it;

	for (tile_it = allTiles.begin(); tile_it != allTiles.end(); tile_it++) {
		for (path_it = (*tile_it)->adjacent.begin(); path_it != (*tile_it)->adjacent.end(); path_it++) {
			delete *path_it;
		}
		delete *tile_it;
	}
}


/* Runs Dijkstra's algorithm (modified breadth first search) on the game board to find the path with the lowest 
 * total cost from the start to the goal tile */

void Map::Dijkstra() {

	char type;
	int cost;
	Tile *tile;
	std::list <Tile *>::iterator tile_it;
	std::list <Path *>::iterator adj_it;

	/* Set all nodes' backedges to NULL and best costs to -1 */

	for (tile_it = allTiles.begin(); tile_it != allTiles.end(); tile_it++) {
		(*tile_it)->backedge = NULL;
		(*tile_it)->bestCost = -1;
	}

	/* Set the starting tile's best cost to 0 and put it in the queue */

	start->bestCost = 0;
	queue.insert( std::pair<int, Tile *>(start->bestCost, start) );

	while (!queue.empty()) {
		
		/* Remove a node from the front of the queue */

		tile = queue.begin()->second;
		queue.erase( queue.begin() );

		/* Go through the tile's adjacency list */

		for (adj_it = tile->adjacent.begin(); adj_it != tile->adjacent.end(); adj_it++) {
			
			/* Calculate cost to get to next tile */

			cost = 0;
			type = tile->type;
			it = TILE_TYPES.find(type);
			cost += it->second + tile->bestCost;

			/* If a new shortest path is found, update the bestCost and backedges before putting the tile in the queue */

			if ((*adj_it)->to->bestCost == -1 || (*adj_it)->to->bestCost > cost) {
				
				(*adj_it)->to->bestCost = cost;
				(*adj_it)->to->backedge = *adj_it;
				queue.insert( std::pair<int, Tile *>(cost, (*adj_it)->to) );
			}
		}
	}

	/* Traverse backedges from *goal and create the path */

	tile = goal;
	while (tile->backedge != NULL) {
		path.push_front(tile->backedge);
		tile = tile->backedge->from;
	}

	/* Print out best cost to get to goal tile */

	std::cout << goal->bestCost << std::endl;
}


/* Goes through path list and prints out the quickest path */

void Map::PrintPath() {

	std::list <Path *>::iterator path_it;

	std::cout << (*path.begin())->from->x << " " << (*path.begin())->from->y << std::endl;
	
	for (path_it = path.begin(); path_it != path.end(); path_it++) {
		std::cout << (*path_it)->to->x << " " << (*path_it)->to->y << std::endl;
	}
}
