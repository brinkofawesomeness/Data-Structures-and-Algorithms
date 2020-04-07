all: solution

solution: solution.o dllist.o
	g++ solution.o dllist.o -o solution

solution.o: solution.cpp
	g++ -c solution.cpp

dllist.o: dllist.cpp
	g++ -c dllist.cpp

clean:
	rm *.o solution
