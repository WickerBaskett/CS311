all: player_test

player_test: player_test.cpp player.hpp player.cpp
	g++ -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++17 -o main player.cpp player_test.cpp
