#!make -f

#CXX=clang++-9 
CXX=gcc
CXXFLAGS= -Wall -g

HEADERS=AdptArray.h book.h Person.h 
OBJECTS=AdptArray.o book.o Person.o Main.o
SOURCES=AdptArray.c book.c Person.c Main.c

run: demo
	./$^

mem_test: demo
	valgrind ./$^

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

Main: Maim.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o Main

%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo
