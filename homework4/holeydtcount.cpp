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
void printBoard(vector<int> board, size_t dim_x)
{
    for (size_t i = 0; i < dim_x; ++i)
    {
        std::cout << "--";
    }

    std::cout << std::endl;

    for (size_t i = 0; i < board.size(); ++i)
    {
            if (board[i] == 0)
                std::cout << "x ";
            else if (board[i] == 1)
                std::cout << "o ";
            if((i+1) % dim_x == 0)
                std::cout << std::endl;
    }

    for (size_t i = 0; i < dim_x; ++i)
    {
        std::cout << "--";
    }

    std::cout << std::endl;
}

// if dir is 0 we are testing a vertical domino,
//   if dir is not 0 we are testing a horizontal domino
bool validDomino(const vector<int> & board, size_t dim_x, size_t tile, int dir)
{
    // Find location of second tile in domino
    size_t sec_tile = tile;
    if (dir == 0) // Vertical Shift
    {
        sec_tile = tile + dim_x;
    }
    else          // Horizontal Shift
    {
        // Make sure the tile is not on the edge of a row
        if (tile % dim_x == dim_x - 1)
            return false;

        sec_tile += 1;
        
    }

    // Check if the second tile of the domino is on the board
    if (sec_tile >= board.size())
        return false;
    
    
    
    // Check if the tile occupied by the second domino is covered
    return (board[sec_tile] == 0);
}

// Takes the dimensions of a board and the location of two holes,
//   returns the number of possible way to cover the board in dominos
int holeyDTCount(int dim_x, int dim_y,
                 int hole1_x, int hole1_y,
                 int hole2_x, int hole2_y)
{
    int squares_left = (dim_x * dim_y) - 2;

    // Observe that a domino takes up two tiles and we have two holes,
    // thus we can express the total number of covered tiles as 2n + 2
    // where n is the number of dominos on the board. This can be factored into
    // 2(n + 1) which will always be an even number so if the number of tiles
    // present on the board is not even then we have no possible solutions
    if (squares_left % 2 != 0)
        return 0;

    // The board is stored in rows, ie. if dim_x is 4 then [0,3] represent the first row,
    // [4,7] the second row, [8,11] the third and so on until we have dim_y rows.
    //
    // Ex: A 4x3 board, numbers represent the index in board
    //      
    // 0  1  2  3
    // 4  5  6  7
    // 8  9  10 11
    //
    // A 0 represents an uncovered tile while a 1 represents a covered tile
    vector<int> board(static_cast<size_t>(squares_left + 2), 0);


    // Fill in the holes on the board
    board[static_cast<size_t>((hole1_y * dim_x) + hole1_x)] = 1;
    board[static_cast<size_t>((hole2_y * dim_x) + hole2_x)] = 1;

    size_t x_dim = static_cast<size_t>(dim_x);

    return holeyDTCount_recurse(board, x_dim, squares_left);
}


// Workhorse function, uses recursive backtracking to solve the problem
int holeyDTCount_recurse(vector<int> & board, size_t dim_x, int squares_left)
{
    // If we filled the board then we have a solution;
    if (squares_left == 0)
    {
        return 1;
    }

    size_t tile;

    // Find first uncovered tile
    for (size_t i = 0; i < board.size(); ++i)
    {
        if(board[i] == 0)
        {
            tile = i;
            break;
        }
    }

    int sum = 0;

    // See if we can place a vertical domino
    if (validDomino(board, dim_x, tile, 0))
    {
        board[tile] = 1;
        board[tile + dim_x] = 1;

        sum += holeyDTCount_recurse(board, dim_x, squares_left - 2);

        board[tile] = 0;
        board[tile + dim_x] = 0;
    }

    // See if we can place a horizontal domino
    if (validDomino(board, dim_x, tile, 1))
    {
        board[tile] = 1;
        board[tile + 1] = 1;

        sum += holeyDTCount_recurse(board, dim_x, squares_left - 2);

        board[tile] = 0;
        board[tile + 1] = 0;
    }

    return sum;
}
