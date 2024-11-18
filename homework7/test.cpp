#include "treesort.hpp"

#include <iterator>
// For std::iterator_traits
#include <memory>
// For std::unique_ptr
// For std::make_unique
#include <algorithm>
// For std::move
#include <vector>
using std::vector;
#include <iostream>
using std::cout, std::endl;

int main()
{
    std::unique_ptr<BSTreeNode<int>> head = nullptr;

    const vector<int> n
        { 3, 6, 19, -2, 8, 6, 7, 1, 141, -2,
          -200, 4, 6, 6, 11, -5, 32, 2, 7, 0 };
    for (auto ent : n)
    {
        insert(head, ent);
    }
    
    vector<int> buff(20, 0);
    auto iter = buff.begin();
    inorder_traversal(head, iter);

    cout << "Manual insert and traverse" << endl;
    for (auto entry : buff)
    {
        cout << entry << ", ";
    }
    

    vector<int> alt_buff(n);

    auto first = alt_buff.begin();
    std::advance(first, 1);
    auto last = alt_buff.end();
    std::advance(last, -1);
    treesort(first, last);
    
    cout << endl << "Treesort" << endl;
    for (auto i : alt_buff)
    {
        cout << i << ", ";
    }
    cout << endl;

}
