all: main

main: treesort_test.cpp treesort.hpp
	g++ -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++ -std=c++17 treesort_test.cpp -o main

test: test.cpp treesort.hpp
	g++ test.cpp -o test
clean:
	rm -f main *.o test

.PHONY: all clean
