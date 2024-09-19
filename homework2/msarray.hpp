// masarray.hpp
// Elliott Lewandowski
// September 19, 2024
//
// For CS311 Homework 2
// Header for class MSArray

#ifndef FILE_MSARRY_HPP_INCLUDED
#define FILE_MSARRY_HPP_INCLUDED

#include <cassert>   // For assert
#include <algorithm> // For std::fill

// Invariants:
//      m_size >= 0
//      m_arrayptr != nullptr
template <typename ValType>
class MSArray 
{ 
    public:
        using value_type = ValType;
        using size_type = size_t;

        // Default ctor
        MSArray() 
            : m_arrayptr(new ValType[8]),
              m_size(8)
        {
            
        }

        // 1-param ctor
        MSArray(u_int num_elements) 
            : m_arrayptr(new ValType[num_elements]),
              m_size(num_elements)
        {

        }

        // 2-param ctor
        MSArray(u_int num_elements, ValType value)
            : m_arrayptr(new ValType[num_elements]),
              m_size(num_elements)
        {
            std::fill(m_arrayptr, m_arrayptr + m_size, value);
        }

        // dtor
        ~MSArray() noexcept
        {
            delete [] m_arrayptr;
        }

        // Copy ctor
        MSArray(const MSArray & other) 
            : m_arrayptr(new ValType[other.m_size]),
              m_size(other.m_size)
        {
            std::copy(other.begin(), other.end(), m_arrayptr);
        }

        // Copy Assignment
        MSArray & operator=(const MSArray & rhs)
        {
            auto rhs_copy = rhs;
            mswap(rhs_copy);
            return *this;
        }

        // Move ctor
        MSArray(MSArray && other) noexcept
            : m_arrayptr(other.m_arrayptr),
              m_size(other.m_size)
        {
            other.m_arrayptr = nullptr;
            other.m_size = 0;
        }

        // Move Assignment
        MSArray & operator=(MSArray && rhs) noexcept
        {
            mswap(rhs);
            return *this;
        }

        // Pre:
        //    index is in range [0, m_size)
        ValType & operator [](size_type index)
        {
            assert(index < m_size);
            return m_arrayptr[index];
        }

        // Pre:
        //    index is in range [0, m_size)
        const ValType & operator [](size_type index) const
        {
            assert(index < m_size);
            return m_arrayptr[index];
        }

        // Pre:
        //    None
        size_type size() const
        {
            return m_size;
        }

        // Pre:
        //    None
        ValType * begin()
        {
            return m_arrayptr;
        }

        // Pre:
        //    None
        const ValType * begin() const
        {
            return m_arrayptr;
        }

        // Pre:
        //    None
        ValType * end()
        {
            return begin() + m_size;
        }

        // Pre:
        //    None
        const ValType * end() const
        {
            return begin() + m_size;
        }

    private:
        ValType *  m_arrayptr;
        size_t m_size;
        
        // Acknowledgment: This function was written by Glenn Chappell
        //      in his lecture notes on Invisible Functions II
        // Pre:
        //    Other must be a valid MSArray Object
        void mswap(MSArray & other) noexcept
        {
            std::swap(m_arrayptr, other.m_arrayptr);
            std::swap(m_size, other.m_size);
        }
}; // End of Class MSArray

// Pre:
//    lhs and rhs must have same ValType
template <typename ValType>
bool operator<(const MSArray<ValType> & lhs, const MSArray<ValType> & rhs)
{
    const ValType * lhs_ptr = lhs.begin();
    const ValType * rhs_ptr = rhs.begin();

    while(lhs_ptr != lhs.end() && rhs_ptr != rhs.end())
    {
            if (*lhs_ptr < *rhs_ptr)
            {
                return true;
            }
            if (*rhs_ptr < *lhs_ptr)
            {
                return false;
            }
        ++lhs_ptr;
        ++rhs_ptr;
    }

    return (lhs.size() < rhs.size());
}

// Pre:
//    lhs and rhs must have same ValType
template <typename ValType>
bool operator<=(const MSArray<ValType> & lhs, const MSArray<ValType> & rhs)
{
    return !(rhs < lhs);
}

// Pre:
//    lhs and rhs must have same ValType
template <typename ValType>
bool operator>(const MSArray<ValType> & lhs, const MSArray<ValType> & rhs)
{
    return (rhs < lhs);
}

// Pre:
//    lhs and rhs must have same ValType
template <typename ValType>
bool operator>=(const MSArray<ValType> & lhs, const MSArray<ValType> & rhs)
{
    return !(lhs < rhs);
}

// Pre:
//    lhs and rhs must have same ValType
template <typename ValType>
bool operator==(const MSArray<ValType> & lhs, const MSArray<ValType> & rhs)
{
    const ValType * lhs_ptr = lhs.begin();
    const ValType * rhs_ptr = rhs.begin();

    if (lhs.size() != rhs.size()) 
    {
        return false;
    }

    // We know the sizes of lhs and rhs are equal here so we only
    //   need to check one for the loop
    while(lhs_ptr != lhs.end())
    {
        if (*lhs_ptr != *rhs_ptr)
        {
            return false;
        }

        ++lhs_ptr;
        ++rhs_ptr;
    }

    return true;
}

// Pre:
//    lhs and rhs must have same ValType
template <typename ValType>
bool operator!=(const MSArray<ValType> & lhs, const MSArray<ValType> & rhs)
{
    return !(lhs == rhs);
}

#endif // FILE_MSARRY_HPP_INCLUDED
