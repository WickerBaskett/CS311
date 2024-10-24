#include "holeydtcount.hpp"

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int sum = holeyDTCount(8,8, 
                           2,0, 
                           3,0);

    cout << "Solutions: " << sum << endl;
}
