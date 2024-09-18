// masarray.hpp
// Elliott Lewandowski
// September 18, 2024
//
// For CS311 Homework 2
// Header for class MSArray

#ifndef FILE_MSARRY_HPP_INCLUDED
#define FILE_MSARRY_HPP_INCLUDED

#include <cstddef>

template <typename ValType>
class MSArray 
{ 
    public:
        using value_type = ValType;
        using size_type = size_t;

        // Default ctor
        MSArray() 
        {
            
        }

        // 1-param ctor
        MSArray(int num_elements) 
        {

        }

        // 2-param ctor
        MSArray(int num_elements, ValType value) 
        {

        }

        // dtor
        ~MSArray() 
        {
            delete m_array;
        }

        // Copy ctor
        MSArray(const MSArray<ValType> & other) 
        {

        }

        // Copy Assignment
        MSArray & operator=(const MSArray<ValType> & rhs) 
        {

        }

        // Move ctor
        MSArray(MSArray && other) 
        {

        }

        // Move Assignment
        MSArray<ValType> & operator=(MSArray<ValType> && other) 
        {

        }

        ValType & operator [](size_type index)
        {

        }

        const ValType & operator [](size_type index) const
        {

        }

        size_type size() const
        {
            
        }

        ValType * begin()
        {

        }

        const ValType * begin() const
        {

        }

        ValType * end()
        {

        }

        const ValType * end() const
        {

        }

        bool operator==(const MSArray<ValType> & rhs) const
        {

        }

        bool operator!=(const MSArray<ValType> & rhs) const
        {

        }

        bool operator<(const MSArray<ValType> & rhs) const
        {

        }

        bool operator<=(const MSArray<ValType> & rhs) const
        {

        }

        bool operator>(const MSArray<ValType> & rhs) const
        {

        }

        bool operator>=(const MSArray<ValType> & rhs) const
        {

        }

    private:
        size_t m_size;
        ValType *  m_array;
};
#endif // FILE_MSARRY_HPP_INCLUDED
