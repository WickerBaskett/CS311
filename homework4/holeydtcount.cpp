// holeydtcount.cpp
// Elliott R. Lewandowski
// October 8, 2024
//
// For CS311 Homework 4
// Source1 for holeyDTCount, a solver for the
//   holey domino problem

#include "holeydtcount.hpp"

using std::size_t;
using std::vector;
using std::pair;

int holeyDTCount_recurse(vector<int> & board, size_t dim_x, size_t squares_left);

// If dir is 0 we are testing a vertical domino,
//   If dir is not 0 we are testing a horizontal domino
//
// Preconditions:
//      board is a properly allocated vector<int>
//      board is of length dim_x * dim_y
//      dim_x accurately represents the x dimension of the board
// Possible Exceptions: 
//      Does not throw
bool validDomino(const vector<int> & board, size_t dim_x, size_t tile, int dir)
{
    // Find location of second tile in domino
    size_t sec_tile = tile;
    if (dir == 0) // Vertical Shift
    {
        sec_tile += dim_x;
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
    size_t squares_left = static_cast<size_t>((dim_x * dim_y) - 2);

    // Observe that a domino takes up two tiles and we have two holes,
    // thus we can express the total number of covered tiles as 2n + 2
    // where n is the number of dominos on the board. This can be factored into
    // 2(n + 1) which will always be an even number therefore if the  total number 
    // of tiles present on the board is not even then we have no possible solutions
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
    vector<int> board(squares_left + 2, 0);


    // Fill in the holes on the board
    board[static_cast<size_t>((hole1_y * dim_x) + hole1_x)] = 1;
    board[static_cast<size_t>((hole2_y * dim_x) + hole2_x)] = 1;

    return holeyDTCount_recurse(board, static_cast<size_t>(dim_x), squares_left);
}


// Workhorse function, uses recursive backtracking to solve the problem
//
// Preconditions:
//      board is a properly allocated vector<int>
//      board is of length dim_x * dim_y
//      squares_left accuratley represents the number of remaining squares on the board
//      dim_x accuratley represents the x dimension of the board
//
// Possible Exceptions: 
//      Does not throw
int holeyDTCount_recurse(vector<int> & board, size_t dim_x, size_t squares_left)
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
