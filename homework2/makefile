all: msarray

msarray: msarray_test.cpp msarray.hpp doctest.h
	g++ -std=c++17 -o main msarray_test.cpp

clean:
	rm -f main

.PHONY: all clean

#-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++ 
