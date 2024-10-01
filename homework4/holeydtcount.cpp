// holeydtcount.cpp
// Elliott R. Lewandowski
// September 30, 2024
//
// For CS311 Homework 4
// Source for 

#include "holeydtcount.hpp"

#include <iostream> // For std::cout, std::endl

using std::size_t;
using std::vector;
using std::pair;


// Debug function to visualize current state of the board
void printBoard(vector<vector<int>> board)
{
    for (size_t i = 0; i < board.size(); ++i)
    {
        std::cout << "--";
    }

    std::cout << std::endl;

    for (auto row : board)
    {
        for(auto col : row)
        {
            if (col == 0)
                std::cout << "x ";
            else if (col == 1)
                std::cout << "o ";
            else
                std::cout << "H ";
        }
        std::cout << std::endl;
    }

    for (size_t i = 0; i < board.size(); ++i)
    {
        std::cout << "--";
    }

    std::cout << std::endl;
}

// if dir is 0 we are testing a vertical domino,
//   if dir is not 0 we are testing a horizontal domino
// preconditions:
//      tile must be passed as a (y,x) pair where x && y >= 0
bool validDomino(const vector<vector<int>> board, const pair<size_t, size_t> & dim, const pair<size_t, size_t> & tile, int dir)
{

    // If the initial square of the domino is off the board we dont need any more logic
    if (tile.first > dim.first || tile.second > dim.second)
        return false;

    // Find location of second tile in domino
    pair<size_t, size_t> sec_tile = tile;
    if (dir == 0) // Vertical Shift
    {
        sec_tile.first += 1;
    }
    else          // Horizontal Shift
    {
        sec_tile.second += 1;
    }

    if ((sec_tile.first >= dim.first) || (sec_tile.second >= dim.second))
        return false;
    
    return (board[sec_tile.first][sec_tile.second] == 0);
}

int holeyDTCount(int dim_x, int dim_y,
                 int hole1_x, int hole1_y,
                 int hole2_x, int hole2_y)
{
    int squares_left = (dim_x * dim_y) - 2;

    // A domino takes up two tiles, we have an even number of holes,
    // thus we can express the total number of covered tiles as 2n + 2
    // where n is the number of dominos on the board. This can be factored into
    // 2(n + 1) which will always be an even number so if the number of tiles
    // present on the board is not even then we have no possible solutions
    if (squares_left % 2 != 0)
        return 0;

    // Board stores coordinates as [y][x], a 0 is an empty tile, a 1 is a filled tile
    vector<vector<int>> board(static_cast<size_t>(dim_y), vector<int>(static_cast<size_t>(dim_x), 0));

    // Fill in the holes on the board
    board[static_cast<size_t>(hole1_y)][static_cast<size_t>(hole1_x)] = 1;
    board[static_cast<size_t>(hole2_y)][static_cast<size_t>(hole2_x)] = 1;

    pair<size_t, size_t> dim(static_cast<size_t>(dim_y), static_cast<size_t>(dim_x));

    return holeyDTCount_recurse(board, dim, squares_left);
}


// Workhorse function, uses recursive backtracking to solve the problem
int holeyDTCount_recurse(vector<vector<int>> & board, const pair<size_t, size_t> & dim, int squares_left)
{
    // If we filled the board then we have a solution;
    if (squares_left == 0)
    {
        return 1;
    }

    pair<size_t, size_t> tile;
    bool found = false;

    // n^2
    // Find first uncovered tile
    for (size_t y = 0; y < dim.first; ++y)
    {
        for (size_t x = 0; x < dim.second; ++x)
        {
            if (board[y][x] == 0)
            {
                tile = pair<size_t, size_t>(y, x);
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    int sum = 0;

    // See if we can place a vertical domino
    if (validDomino(board, dim, tile, 0))
    {
        board[tile.first][tile.second] = 1;
        board[tile.first + 1][tile.second] = 1;

        sum += holeyDTCount_recurse(board, dim, squares_left - 2);

        board[tile.first][tile.second] = 0;
        board[tile.first + 1][tile.second] = 0;
    }

    // See if we can place a horizontal domino
    if (validDomino(board, dim, tile, 1))
    {
        board[tile.first][tile.second] = 1;
        board[tile.first][tile.second + 1] = 1;

        sum += holeyDTCount_recurse(board, dim, squares_left - 2);

        board[tile.first][tile.second] = 0;
        board[tile.first][tile.second + 1] = 0;
    }

    return sum;
}