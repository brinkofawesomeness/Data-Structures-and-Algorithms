CXX=		g++
CXXFLAGS=	-Wall
SHELL=		bash
PROGRAMS=	src/dijkstras generate_map

all:		src/dijkstras generate_map

dijkstras:	src/dijkstras.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

generate_map:  generate_map.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY:		test test-output test-memory clean

clean:
	rm -f $(PROGRAMS)

test:		test-output test-memory

test-output:	src/dijkstras
	@echo Testing output 0...
	@cat data/input0.txt <(./src/dijkstras < data/input0.txt) | ~tmn678/public/checkproj4 data/output0.txt
	@echo Testing output 1...
	@cat data/input1.txt <(./src/dijkstras < data/input1.txt) | ~tmn678/public/checkproj4 data/output1.txt
	@echo Testing output 2...
	@cat data/input2.txt <(./src/dijkstras < data/input2.txt) | ~tmn678/public/checkproj4 data/output2.txt
	@echo Testing output 3...
	@cat data/input3.txt <(./src/dijkstras < data/input3.txt) | ~tmn678/public/checkproj4 data/output3.txt

test-memory:	src/dijkstras
	@echo Testing memory...
	@[ `valgrind --leak-check=full ./src/dijkstras < data/input1.txt 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]
