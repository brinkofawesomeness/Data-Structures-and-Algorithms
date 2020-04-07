CXX = g++
RM = rm
CFLAGS = -Wall
EXECUTABLE = volsort

all: $(EXECUTABLE)

$(EXECUTABLE): dllist.o volsort.o compare.o stl.o qsort.o merge.o quick.o
	g++ dllist.o volsort.o compare.o stl.o qsort.o merge.o quick.o -o volsort
	rm *.o

dllist.o: dllist.cpp
	g++ -c dllist.cpp

volsort.o: volsort.cpp
	g++ -c volsort.cpp

compare.o: compare.cpp
	g++ -c compare.cpp

stl.o: stl.cpp
	g++ -c stl.cpp

qsort.o: qsort.cpp
	g++ -c qsort.cpp

merge.o: merge.cpp
	g++ -c merge.cpp

quick.o: quick.cpp
	g++ -c quick.cpp

clean:
	$(RM) $(EXECUTABLE)
