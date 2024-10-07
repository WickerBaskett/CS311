// holeydtcount.hpp
// Elliott R. Lewandowski
// September 30, 2024
//
// For CS311 Homework 4
// Header for 
#ifndef FILE_HOLEYDTCOUNT_HPP_INCLUDED
#define FILE_HOLEYDTCOUNT_HPP_INCLUDED

#include <vector>  // For std::vector
#include <cstddef> // For std::size_t

int holeyDTCount(int dim_x, int dim_y,
                 int hole1_x, int hole1_y,
                 int hole2_x, int hole2_y);

int holeyDTCount_recurse(std::vector<int> & board, std::size_t dim, int squares_left);

#endif // FILE_HOLEYDTCOUNT_HPP_INCLUDED
