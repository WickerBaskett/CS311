// player.cpp
// Elliott Lewandowski
// September 5, 2024
//
// For CS311 Homework 0
// Source for class Player

#include "player.hpp"

std::ostream & operator<<(std::ostream & out, const Player & player)
{
    out << player.toString();
    return out;
}

bool operator==(const Player & lhs, const Player & rhs)
{
    if ((lhs.getRealName() == rhs.getRealName()) 
        && (lhs.getUsername() == rhs.getUsername())
        && (lhs.getGames() == rhs.getGames()))
    {
        return true;
    }

    return false;
}

bool operator!=(const Player & lhs, const Player & rhs)
{
    return !(lhs == rhs);
}

