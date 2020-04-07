/*
 * Conner Brinkley
 * March 15, 2019
 * Project 04 -- Generating Map for Path Finding
 *
 * INPUT:  N on the command line, where N is a dimension of an N x N grid.
 * OUTPUT: A randomly generated map that can be piped to dijkstras.cpp
 *
 * */

#include <ctime>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
	
	/* Read in N */

	int N;
	N = atoi(argv[1]);

	/* Print out number of tiles, the tile types with their costs, and the dimensions */

	std::cout << 6 << std::endl;

	std::cout << "f " << 3 << std::endl;
	std::cout << "g " << 1 << std::endl;
	std::cout << "G " << 2 << std::endl;
	std::cout << "h " << 4 << std::endl;
	std::cout << "m " << 7 << std::endl;
	std::cout << "r " << 5 << std::endl;

	std::cout << N << " " << N << std::endl;

	/* Randomly generate the board */

	int i, j;
	char tile[] = { 'f', 'g', 'G', 'h', 'm', 'r' };
	srand(time(0));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			std::cout << tile[ rand() % 6 ] << " ";
		}
		std::cout << std::endl;
	}

	/* Print out start and goal cells */

	std::cout << 0 << " " << 0 << std::endl;
	std::cout << N-1 << " " << N-1 << std::endl;
	
	return 0;
}
