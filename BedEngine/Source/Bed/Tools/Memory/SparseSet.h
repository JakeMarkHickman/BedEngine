#pragma once

#include <vector>

namespace Bed
{
    // TODO: include core.h as to be able to use sparce arrays within games/editor
    template<typename T>
    class SparseSet
    {
    public:

        void Insert(uint64_t id, T data)
        {
            if(id >= m_Sparse.size()) // Checks to see if id is greater than or equal to the size of the sparce vector
            {
                m_Sparse.resize(id + 1, -1); // Resizes the sparce vector and sets the index for dense vector to -1
            }

            if(m_Sparse[id] == -1) // Checks to see if the index is -1
            {
                m_Sparse[id] = m_Dense.size();
                m_Dense.push_back(id);
                m_Data.push_back(data);
            }
            else
            {
                m_Data[m_Sparse[id]] = data;
            }
        }

        void Remove(uint64_t id)
        {
            if(id < m_Sparse.size() && m_Sparse[id] != -1) // checks if id is smaller than sparce vector and if the index is not equal to -1
            {
                uint64_t index = m_Sparse[id];
                uint64_t lastId = m_Dense.back();

                m_Dense[index] = lastId;
                m_Sparse[lastId] = index;

                m_Dense.pop_back();
                m_Data[index] = m_Data.back();
                m_Data.pop_back();

                m_Sparse[id] = -1; 
            }
        }

        bool HasIndex(uint64_t id) const
        {
            return id < m_Sparse.size() && m_Sparse[id] != -1;
        }

        T* GetData(uint64_t id)
        {
            if(id < m_Sparse.size() && m_Sparse[id] != -1)
            {
                return m_Data[m_Sparse[id]].get();
            }

            return nullptr;
        }

        /*void SetData(uint64_t id, const T& data)
        {
            m_Data[m_Sparse[id]] = data;
        }*/

        const std::vector<uint64_t>& GetIDs() const
        {
            return m_Dense;
        }

        void Clear()
        {
            m_Sparse.clear();
            m_Dense.clear();
            m_Data.clear();
        }

    private:
        std::vector<int64_t> m_Sparse; // This is used to map the ID to its index in the Dense vector
        std::vector<uint64_t> m_Dense; // Stores the actual ID in a compact manner
        std::vector<T> m_Data; // Stores the Data associated with the ID
    };
}