#include "holeydtcount.hpp"

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int sum = holeyDTCount(4, 1, 
                           0, 0, 
                           0, 1);

    cout << "Solutions: " << sum << endl;
}
