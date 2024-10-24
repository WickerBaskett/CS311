all: main

main: gfsarray_test.cpp gfsarray.o
	g++ -o main gfsarray.o gfsarray_test.cpp
	
gfsarray.o: gfsarray.cpp gfsarray.hpp
	g++ -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++ -std=c++17 -c gfsarray.cpp

clean:
	rm -f main *.o test

.PHONY: all clean

#-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++ -std=c++17 -o main gfsarray.o gfsarray_test.cpp

