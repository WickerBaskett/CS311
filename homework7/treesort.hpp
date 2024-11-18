// treesort.hpp 
// Elliott R. Lewandowski
// 2024-11-18
//
// For CS 311 Fall 2024
// Header for function template treesort
// There is no associated source file.

// Acknowledgments: Glenn G. Chappell wrote the skeleton for this file

#ifndef FILE_TREESORT_HPP_INCLUDED
#define FILE_TREESORT_HPP_INCLUDED

#include <iterator>
// For std::iterator_traits
#include <memory>
// For std::unique_ptr
// For std::make_unique
#include <algorithm>
// For std::move

// A node in a Binary Search Tree (BST)
// Class Invariants:
//   _left/_right are either a unique_ptr to a BSTreeNode or nullptr
//   _data will always be an initialized ValType
template<typename ValType>
struct BSTreeNode {
    ValType _data;
    std::unique_ptr<BSTreeNode<ValType>> _left;
    std::unique_ptr<BSTreeNode<ValType>> _right;

    // 1- & 2- & 3- param ctor
    // _data is set to data (given). _left/_right is set to left/right, if given, or
    // nullptr if not.
    // Exceptions:
    //   any exceptions thrown by the constructor of value
    // Strong Guarantee
    explicit BSTreeNode(const ValType & data,
                     std::unique_ptr<BSTreeNode> left = nullptr,
                     std::unique_ptr<BSTreeNode> right = nullptr)
        :_data(data),
         _left(std::move(left)),
         _right(std::move(right))
    {}
};

// Insert a new item into a BST
// Preconditions:
//    head must point to a properly allocated BST Node
// Exceptions:
//    std::bad_alloc, any exceptions thrown by the constructor of Value
// Strong Guarantee
// Exception-Neutral
template<typename Value>
void insert(std::unique_ptr<BSTreeNode<Value>> & head,
const Value & item) 
{
    // BASE CASE
    if (!head)
    {
        head = std::make_unique<BSTreeNode<Value>>(item);
        return;
    }

    // RECURSIVE CASE
    if (item < head->_data)
    {
        insert(head->_left, item);
    }
    else
    {
        insert(head->_right, item);
    }
}

// Copy the contents of a BST to the memory pointed to by first using
//   an in-order traversal
// Preconditions:
//    head must point to a properly allocated BST Node
//    first must point to memory that is at least as large as
//       the number of nodes in the BST
// No-Throw Guarantee
// Exception-Neutral
template<typename Value, typename FDIter>
void inorder_traversal(const std::unique_ptr<BSTreeNode<Value>> & head,
        FDIter & first)
{
    if (!head)
    {
        return;
    }

    inorder_traversal(head->_left, first);

    *first = head->_data;
    std::advance(first, 1);

    inorder_traversal(head->_right, first);
}

// treesort
// Preconditions:
//    first and last must define the range [first, last)
// Exceptions:
//    std::bad_alloc, any exceptions thrown by the constructor of Value
// Strong Guarantee
// Exception-Neutral
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Value is the type that FDIter points to
    using Value = typename std::iterator_traits<FDIter>::value_type;
    
    std::unique_ptr<BSTreeNode<Value>> head = nullptr;

    for (FDIter iter = first; iter != last; std::advance(iter, 1))
    {
        insert(head, *iter);
    }
    
    inorder_traversal(head, first);
}

#endif //#ifndef FILE_TREESORT_HPP_INCLUDED

