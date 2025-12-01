#pragma once

#include <vector>

namespace Frame
{
    template<typename T, typename U>
    class Bimap
    {
    public:
        void Insert(T left, U right)
        {

        }

        void Remove(uint64_t index)
        {

        }

        void Swap(uint64_t index, uint64_t indexToSwap)
        {

        }

    private:
    //TODO: if wanting any type this needs to be a map
        std::vector<T> m_Left;
        std::vector<U> m_Right;

        std::vector<uint64_t> m_LeftToRight;
        std::vector<uint64_t> m_RightToLeft; 
    }
}