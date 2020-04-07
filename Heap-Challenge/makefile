all: solution

solution: heap.o solution.o
	g++ heap.o solution.o -o solution

heap.o: heap.cpp
	g++ -c heap.cpp

solution.o: solution.cpp
	g++ -c solution.cpp

clean:
	rm *.o
	rm solution
