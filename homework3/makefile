all: da3

da3: da3.cpp da3.hpp doctest.h da3_test.cpp llnode.hpp
	g++ -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++ -std=c++17 -o main da3.cpp da3_test.cpp

clean:
	rm -f main

.PHONY: all clean
