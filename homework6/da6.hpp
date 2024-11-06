
#ifndef FILE_DA6_HPP_INCLUDED
#define FILE_DA6_HPP_INCLUDED

#include <memory>
// For std::unique_ptr, std::make_unique
#include <utility>
// For std::pair, std::move
#include <functional>
// For std::function
#include <stdexcept>
// For std::out_of_range

#include "llnode2.hpp"
// For LLNode2

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
    SLLMap()                   
      : _head(nullptr)
    {}

    // Dtor
    ~SLLMap() noexcept 
    {

    }
    
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
    size_type size() const 
    {
        auto curr = _head.get();
        size_type count(0);

        while(curr != nullptr)
        {
            count += 1;
            curr = curr->_next.get();
        }

        return count;
    }

    bool empty() const 
    {
        return !(_head);
    }

    bool present(key_type key) const 
    {
        auto curr = _head.get();

        while (curr != nullptr)
        {
            if (curr->_data.first == key)
            {
                return true;
            }
            curr = curr->_next.get();
        }    

        return false;
    }

    data_type & get(key_type key) 
    {
        auto curr = _head.get();

        while (curr != nullptr)
        {
            if (curr->_data.first == key)
            {
                return curr->_data.second;
            }
            curr = curr->_next.get();
        }    

        throw std::out_of_range("Key not found in SLLMap");
    }

    const data_type & get(key_type key) const 
    {
        auto curr = _head.get();

        while (curr != nullptr)
        {
            if (curr->_data.first == key)
            {
                return curr->_data.second;
            }
            curr = curr->_next.get();
        }    

        throw std::out_of_range("Key not found in SLLMap");
    }

    void set(key_type key, data_type data) 
    {
        auto curr = _head.get();

        while (curr != nullptr)
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

    void erase(key_type key) 
    {
        auto curr = _head.get();
        auto prior = curr;

        while (curr != nullptr)
        {
            if (curr->_data.first == key)
            {
                prior->_next = std::move(curr->_next);
                return;
            }
            prior = curr;
            curr = curr->_next.get();
        } 
    }

    void traverse(std::function<void(key_type,data_type)> func)
    {
        auto curr = _head.get();

        while (curr != nullptr)
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
