
#ifndef FILE_DA6_HPP_INCLUDED
#define FILE_DA6_HPP_INCLUDED

#include <memory>
// For std::unique_ptr
#include <utility>
// For std::pair, std::move
#include <functional>
// For std::function

#include "llnode2.hpp"
// For LLNode2

template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>> & head) {
    std::unique_ptr<LLNode2<ValType>> newHead = nullptr;
    std::unique_ptr<LLNode2<ValType>> storage = nullptr;
    
    while(head != nullptr)
    {
        storage = std::move(newHead);
        newHead = std::move(head);
        head = std::move(head->_next);
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

// ***** SLLMap: Member Functions *****
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

    size_type size() const 
    {
        // TO-DO: Write this!!!
    }

    bool empty() const 
    {
        // TO-DO: Write this!!!
    }

    bool present(key_type key) const 
    {
        // TO-DO: Write this!!!
    }

    data_type & get(key_type key) {
        // TO-DO: Write this!!!
    }

    const data_type & get(key_type key) const {
        // TO-DO: Write this!!!
    }

    void set(key_type key, data_type data) {
        // TO-DO: Write this!!!
    }

    void erase(key_type key) {
        // TO-DO: Write this!!!
    }

    void traverse(std::function<void(key_type,data_type)>)
    {
        // TO-DO: Write this!!!
    }

// ***** SLLMap: data members *****
private:
    std::unique_ptr<LLNode2<std::pair<key_type, data_type>>> _head;

}; // End of class SLLMap

#endif //FILE_DA6_HPP_INCLUDED
