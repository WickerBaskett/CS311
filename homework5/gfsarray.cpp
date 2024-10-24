// GFSArray.cpp  HAND-OFF
// VERSION 6
// Glenn G. Chappell
// Started: 2024-10-15
// Updated: 2024-10-23
//
// For CS 311 Fall 2024
// Source for class GFSArray
// Frightfully smart array of int
// Preliminary to Assignment 5


#include "gfsarray.hpp"  // For class GFSArray definition
#include <algorithm>
using std::copy;


// *********************************************************************
// class GFSArray - Member function definitions
// *********************************************************************


// Copy ctor
// See header for info.
template <typename ValType>
GFSArray<ValType>::GFSArray(const GFSArray & other)
    :_capacity(other._capacity),
     _size(other.size()),
     _data(other._capacity == 0 ? nullptr
                                : new value_type[other._capacity])
{
    copy(other.begin(), other.end(), begin());
    // The above call to std::copy does not throw, since it copies int
    // values. But if value_type is changed, then the call may throw, in
    // which case this copy ctor may need to be rewritten.
}


// Move ctor
// See header for info.
template <typename ValType>
GFSArray<ValType>::GFSArray(GFSArray<ValType> && other) noexcept
    :_capacity(other._capacity),
     _size(other._size),
     _data(other._data)
{
    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
}


// Copy assignment operator
// See header for info.
template <typename ValType>
GFSArray<ValType> & GFSArray<ValType>::operator=(const GFSArray<ValType> & other)
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// Move assignment operator
// See header for info.
template <typename ValType>
GFSArray<ValType> & GFSArray<ValType>::operator=(GFSArray<ValType> && other) noexcept
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// resize
// See header for info.
template <typename ValType>
void GFSArray<ValType>::resize(GFSArray<ValType>::size_type newsize)
{
    // TODO: WRITE THIS!!!
}


// insert
// See header for info.
template <typename ValType>
typename GFSArray<ValType>::iterator GFSArray<ValType>::insert(GFSArray<ValType>::iterator pos,
                                  GFSArray<ValType>::value_type item)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// erase
// See header for info.
template <typename ValType>
typename GFSArray<ValType>::iterator GFSArray<ValType>::erase(GFSArray<ValType>::iterator pos)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// swap
// See header for info.
template <typename ValType>
void GFSArray<ValType>::swap(GFSArray<ValType> & other) noexcept
{
    // TODO: WRITE THIS!!!
}

