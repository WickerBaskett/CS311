// holeydtcount.hpp
// Elliott R. Lewandowski
// October 8, 2024
//
// For CS311 Homework 4
// Header for holeyDTCount, a solver for the
//   holey domino problem
#ifndef FILE_HOLEYDTCOUNT_HPP_INCLUDED
#define FILE_HOLEYDTCOUNT_HPP_INCLUDED

#include <vector>  // For std::vector
#include <cstddef> // For std::size_t

// Preconditions:
//      0 < dim_x
//      0 < dim_y
//      0 < hole1_x < dim_x
//      0 < hole1_y < dim_y
//      0 < hole2_x < dim_x
//      0 < hole2_y < dim_y
//
// Possible Exceptions: 
//      Does not throw
int holeyDTCount(int dim_x, int dim_y,
                 int hole1_x, int hole1_y,
                 int hole2_x, int hole2_y);

#endif // FILE_HOLEYDTCOUNT_HPP_INCLUDED
