#include "holeydtcount.hpp"

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int sum = holeyDTCount(8,5, 
                           6,4, 
                           7,4);

    cout << "Solutions: " << sum << endl;
}
