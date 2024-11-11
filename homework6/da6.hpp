// da6.hpp  
// Elliott R. Lewandowski
// Last Revision: 2024-11-07
//
// For CS 311 Fall 2024
// Header for class SLLMap and 
// function reverseList for
// CS311 Assignment 6

#ifndef FILE_DA6_HPP_INCLUDED
#define FILE_DA6_HPP_INCLUDED

#include <memory>
// For std::unique_ptr
#include <utility>
// For std::pair, std::move
#include <functional>
// For std::function
#include <stdexcept>
// For std::out_of_range

#include "llnode2.hpp"
// For LLNode2, pushFront

// Preconditions:
//   head is a std::unique_ptr pointing to a LLNode2 or nullptr
// Exceptions:
//   any exceptions thrown by ValType member functions
template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>> & head) {
    std::unique_ptr<LLNode2<ValType>> newHead = nullptr;
    std::unique_ptr<LLNode2<ValType>> storage = nullptr;
    
    while(head)
    {
        storage = std::move(newHead);
        newHead = std::move(head);
        head = std::move(newHead->_next);
        newHead->_next = std::move(storage);
    }

    head = std::move(newHead);
}


// Invariants:
//      _head points to an LLNode2 allocated with std::make_unique
//        --UNLESS the list is empty in which case _head is nullptr
template<typename KeyType, typename DataType>
class SLLMap {
// ***** SLLMap: types *****
public:

    // key_type: type of keys
    using key_type = KeyType;

    // data_type: type of data items
    using data_type = DataType;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

// ***** SLLMap: Ctors, Dtor *****
public:
    // Default Ctor
    // Exceptions:
    //    std::bad_alloc
    // Strong Guarantee
    // Exception-Neutral
    SLLMap()                   
      : _head(nullptr)
    {}

    // Dtor, Unique pointers clean up after themselves
    // No-Throw Guarantee
    // Exception-Neutral
    ~SLLMap() noexcept 
    {}
    
    // Copy ctor
    SLLMap(const SLLMap & other) = delete;

    // Move ctor
    SLLMap(SLLMap && other) = delete;

    // Copy assignment operator
    SLLMap & operator=(const SLLMap & other) = delete;

    // Move assignment operator
    SLLMap & operator=(SLLMap && other) = delete;

// ***** SLLMap: General Public Operators *****
public:
    // Get the current size of SLLMap
    // Exceptions:
    //    std::bad_alloc
    // Strong Guarantee
    // Exception-Neutral
    size_type size() const 
    {
        auto curr = _head.get();
        size_type count(0);

        while(curr)
        {
            count += 1;
            curr = curr->_next.get();
        }

        return count;
    }

    // Check if the SLLMap is empty
    // No-Throw Guarantee
    // Exception-Neutral
    bool empty() const 
    {
        return !(_head);
    }

    // Check if key is contained in current SLLMap
    // Exceptions:
    //    std::bad_alloc, any exceptions thrown by key_type member functions
    // Strong Guarantee
    // Exception-Neutral
    bool present(key_type key) const 
    {
        auto curr = _head.get();

        while (curr)
        {
            if (curr->_data.first == key)
            {
                return true;
            }
            curr = curr->_next.get();
        }    

        return false;
    }

    // Get a reference to the data corresponding to key
    // Preconditions:
    //    key must be contained in the SLLMap
    // Exceptions:
    //    std::out_of_range, std::bad_alloc,
    //    any exceptions thrown by key_type member functions
    // Strong Guarantee
    // Exception-Neutral
    data_type & get(key_type key) 
    {
        auto curr = _head.get();

        while (curr)
        {
            if (curr->_data.first == key)
            {
                return curr->_data.second;
            }
            curr = curr->_next.get();
        }    

        throw std::out_of_range("Key not found in SLLMap");
    }

    // Get a const reference to the data corresponding to key
    // Preconditions:
    //    key must be contained in the SLLMap
    // Exceptions:
    //    std::out_of_range, std::bad_alloc,
    //    any exceptions thrown by key_type member functions
    // Strong Guarantee
    // Exception-Neutral
    const data_type & get(key_type key) const 
    {
        auto curr = _head.get();

        while (curr)
        {
            if (curr->_data.first == key)
            {
                return curr->_data.second;
            }
            curr = curr->_next.get();
        }    

        throw std::out_of_range("Key not found in SLLMap");
    }

    // Insert or replace an entry in the list
    // Exceptions:
    //    std::bad_alloc,
    //    any exceptions thrown by key_type, or data_type member functions
    // Strong Guarantee
    // Exception-Neutral
    void set(key_type key, data_type data) 
    {
        auto curr = _head.get();

        while (curr)
        {
            if (curr->_data.first == key)
            {
                curr->_data.second = data;
                return;
            }
            curr = curr->_next.get();
        }   

        push_front(_head, std::pair(key, data));
    }

    // Remove an entry from the list
    // Exceptions:
    //    std::bad_alloc,
    //    any exceptions thrown by key_type, or data_type member functions
    // Strong Guarantee
    // Exception-Neutral
    void erase(key_type key) 
    {
        auto curr = _head.get();
        auto prior = curr;

        while (curr)
        {
            if (curr->_data.first == key)
            {
                // Get a unique_ptr to node to remove, allows
                //  dtor to take care of cleanup when toDelete goes
                //  out of scope
                auto toDelete = std::move(prior->_next);
                prior->_next = std::move(curr->_next);
                return;
            }
            prior = curr;
            curr = curr->_next.get();
        } 
    }

    // Calls func on each entry of the current SLLMap
    // Preconditions:
    //    func must take exactly two parameters with types (key_type, data_type)
    // Exceptions:
    //    std::bad_alloc, any exceptions thrown by func, 
    //    any exceptions thrown by key_type, or data_type
    // Basic Guarantee
    // Exception-Neutral
    void traverse(std::function<void(key_type,data_type)> func)
    {
        auto curr = _head.get();

        while (curr)
        {
            func(curr->_data.first, curr->_data.second);
            curr = curr->_next.get();
        }  
    }

// ***** SLLMap: data members *****
private:
    std::unique_ptr<LLNode2<std::pair<key_type, data_type>>> _head;

}; // End of class SLLMap

#endif //FILE_DA6_HPP_INCLUDED
