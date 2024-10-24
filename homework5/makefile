all: main

main: gfsarray_test.o gfsarray.o
	g++ gfsarray.o gfsarray_test.o -o main

gfsarray_test.o: gfsarray_test.cpp
	g++ -c gfsarray_test.cpp

gfsarray.o: gfsarray.cpp gfsarray.hpp
	g++ -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++ -std=c++17 -c gfsarray.cpp

clean:
	rm -f main *.o test

.PHONY: all clean

#-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++ -std=c++17 -o main gfsarray.o gfsarray_test.cpp

