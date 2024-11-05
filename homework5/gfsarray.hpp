// GFSArray.hpp  
// Elliott R. Lewandowski
// Started: 2024-10-15
// Last Updated: 2024-10-30
//
// For CS 311 Fall 2024
// Header for class GFSArray
// Generic frightfully smart array 
// for CS311 Assignment 5

// Acknowledgements: Glenn G. Chappell wrote the skeleton for this class

#ifndef FILE_GFSArray_HPP_INCLUDED
#define FILE_GFSArray_HPP_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max
#include <stdexcept>
// For std::out_of_range

// *********************************************************************
// class GFSArray - Class definition
// *********************************************************************

// If a member function is marked with No-Throw Guarantee the function
//   throws no exceptions so the 'Exceptions: ...' comment has been ommitted
//   for the sake of readability

// class GFSArray
// Frightfully Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of value_type, allocated with new [],
//      owned by *this, holding _capacity value_type values -- UNLESS
//      _capacity == 0, in which case _data may be nullptr.
template<typename ValType>
class GFSArray {

// ***** GFSArray: types *****
public:

    // value_type: type of data items
    using value_type = ValType;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** GFSArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 42 };

// ***** GFSArray: ctors, op=, dctor *****
public:

    // Default ctor & ctor from size
    // Pre:
    //      thesize >= 0
    // Strong Guarantee
    // Exception-Neutral
    // Exceptions:
    //      std::bad_alloc, any exceptions thrown by value_type member functions
    explicit GFSArray(size_type thesize = 0)
        :_capacity(std::max(thesize, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(thesize),
         _data(_capacity == 0 ? nullptr
                              : new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    // Exception-Neutral
    // Exceptions:
    //      std::bad_alloc, any exceptions thrown by value_type member functions
    GFSArray(const GFSArray & other)
        :_capacity(other._capacity),
        _size(other.size()),
        _data(nullptr)
    {
        try {
            if (other._capacity > 0)
            {
                _data = new value_type[other._capacity];
            }
            std::copy(other.begin(), other.end(), begin());
        }
        catch (...)
        {
            delete [] _data;
            throw;
        }
    }

    // Move ctor
    // No-Throw Guarantee
    // Exception-Neutral
    GFSArray(GFSArray && other) noexcept
        :_capacity(other._capacity),
         _size(other._size),
         _data(other._data)
    {
        other._capacity = 0;
        other._size = 0;
        other._data = nullptr;
    }

    // Copy assignment operator
    // Strong Guarantee
    // Exception-Neutral
    // Exceptions:
    //      any exceptions thrown by value_type copy constructor
    GFSArray<ValType> & operator=(const GFSArray<ValType> & other)
    {
        auto other_copy = other;
        swap(other_copy);
        return *this;
    }


    // Move assignment operator
    // No-Throw Guarantee
    // Exception-Neutral
    GFSArray & operator=(GFSArray && other) noexcept
    {
        swap(other);
        return *this;
    }

    // Dctor
    // No-Throw Guarantee
    // Exception-Neutral
    ~GFSArray()
    {
        delete [] _data;
    }

// ***** GFSArray: general public operators *****
public:

    // operator[] - non-const & const
    // Pre:
    //     index is in the range [0, _size - 1]
    // No-Throw Guarantee
    // Exception-Neutral
    value_type & operator[](size_type index)
    {
        return _data[index];
    }
    const value_type & operator[](size_type index) const
    {
        return _data[index];
    }

// ***** GFSArray: general public functions *****
public:

    // size
    // No-Throw Guarantee
    // Exception-Neutral
    size_type size() const noexcept
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    // Exception-Neutral
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    // Exception-Neutral
    iterator begin() noexcept
    {
        return _data;
    }
    const_iterator begin() const noexcept
    {
        return _data;
    }

    // end - non-const & const
    // No-Throw Guarantee
    // Exception-Neutral
    iterator end() noexcept
    {
        return begin() + size();
    }
    const_iterator end() const noexcept
    {
        return begin() + size();
    }

    // resize
    // Pre:
    //      newSize >= 0
    // Strong Guarantee
    // Exception-Neutral
    // Exceptions:
    //      std::bad_alloc, any exceptions thrown by value_type member functions
    void resize(size_type newSize)
    {
        if (newSize <= _capacity)
        {
            _size = newSize;
        }
        else
        {
            size_type newCapacity = (newSize > (_capacity * 2)) ? newSize
                    : (_capacity * 2);

            value_type * newData;

            try {
                newData = new value_type[newCapacity];
                std::copy(begin(), end(), newData);
            } 
            catch (...)
            {
                delete [] newData;
                throw;
            }

            delete [] _data;
            _data = newData;
            _capacity = newCapacity;
            _size = newSize;
        }
    }

    // insert
    // Pre:
    //     pos must be a valid iterator for an element of _data,
    //       we cannot check that this is true in the function
    //       without moving from O(1) to O(n) so we do not
    // Basic Guarantee
    // Exception-Neutral
    // Exceptions:
    //      std::bad_alloc, std::out_of_range, any exceptions thrown by value_type member functions
    iterator insert(iterator pos,
                    const value_type & item)
    {
        // Bounds checking on pos, works because iterator is a value_type *
        if (pos < begin() || pos > end())
        {
            throw std::out_of_range("passed pos is out of range");
        }

        // Save index of pos
        std::ptrdiff_t index = std::distance(begin(), pos);

        resize(_size + 1);

        // Resize might reallocate and copy so we make a new iterator 
        //   at the same index just in case
        iterator new_pos = std::next(begin(), index);
        std::rotate(new_pos, std::next(end(), -1), end());

        *new_pos = item;
        return new_pos;
    }

    // erase
    // Pre:
    //     pos must be a valid iterator for an element of _data
    // Basic Guarantee
    // Exception-Neutral
    // Exceptions:
    //      std::bad_alloc, std::out_of_range, any exceptions thrown by value_type member functions
    iterator erase(iterator pos)
    {
        // Follows std::vectors example, returns last if the array is empty
        if (_size == 0)
        {
            return end();
        }

        // Bounds checking on pos, works because iterator is a value_type *
        if (pos < begin() || pos > end())
        {
            throw std::out_of_range("passed pos is out of range");
        }

        std::rotate(pos, std::next(pos, 1), end());
        resize(_size - 1);
        return pos;
    }

    // push_back
    // Basic Guarantee
    // Exception-Neutral
    // Exceptions:
    //      std::bad_alloc, any exceptions thrown by value_type member functions
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // Pre:
    //     _size must be at least 1
    // Basic Guarantee
    // Exception-Neutral
    // Exceptions:
    //      std::bad_alloc, any exceptions thrown by value_type member functions
    void pop_back()
    {
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    // Exception-Neutral
    void swap(GFSArray & other) noexcept
    {
        std::swap(_capacity, other._capacity);
        std::swap(_size, other._size);
        std::swap(_data, other._data);
    }

// ***** GFSArray: data members *****
private:

    // Below, _capacity must be declared before _data
    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

};  // End class GFSArray


#endif  //#ifndef FILE_GFSArray_HPP_INCLUDED

