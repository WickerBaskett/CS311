// holeydtcount.hpp
// Elliott R. Lewandowski
// September 30, 2024
//
// For CS311 Homework 4
// Header for 
#ifndef FILE_HOLEYDTCOUNT_HPP_INCLUDED
#define FILE_HOLEYDTCOUNT_HPP_INCLUDED

#include <vector> // For std::vector

int holeyDTCount(int dim_x, int dim_y,
                 int hole1_x, int hole1_y,
                 int hole2_x, int hole2_y);

int holeyDTCount_recurse(std::vector<std::vector<int>> & board, const std::pair<int, int> & dim, int squares_left);

#endif // FILE_HOLEYDTCOUNT_HPP_INCLUDED
