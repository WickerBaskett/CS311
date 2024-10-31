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

// *********************************************************************
// class GFSArray - Class definition
// *********************************************************************


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
        _size(other.size())
    {
        try {
            _data = (other._capacity == 0) ? nullptr
                                    : new value_type[other._capacity];
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
    // Does not throw
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
    // Does not throw
    GFSArray & operator=(GFSArray && other) noexcept
    {
        swap(other);
        return *this;
    }

    // Dctor
    // No-Throw Guarantee
    // Exception-Neutral
    // Does not throw
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
    // Does not throw
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
    // Does not throw
    size_type size() const noexcept
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    // Exception-Neutral
    // Does not throw
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    // Exception-Neutral
    // Does not throw
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
    // Does not throw
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
    //     pos must be a valid iterator for an element of _data
    // Basic Guarantee
    // Exception-Neutral
    iterator insert(iterator pos,
                    const value_type & item)
    {
        // Save index of pos
        size_type index = std::distance(begin(), pos);

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
    iterator erase(iterator pos)
    {
        // Follows std::vectors example, returns last if the array is empty
        if (_size == 0)
        {
            return end();
        }
        std::rotate(pos, std::next(pos, 1), end());
        resize(_size - 1);
        return pos;
    }

    // push_back
    // Basic Guarantee
    // Exception-Neutral
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // Pre:
    //     _size must be at least 1
    // Basic Guarantee
    // Exception-Neutral
    void pop_back()
    {
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    // Exception-Neutral
    // Does not throw
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

