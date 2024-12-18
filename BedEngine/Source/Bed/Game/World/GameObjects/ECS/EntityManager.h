#pragma once

#include <vector>

namespace Bed
{
    class EntityManager
    {
    public:
        uint64_t CreateEntity();
        bool DestroyEntity(uint64_t entityToDestroy);

        std::vector<uint64_t> GetAllEntities() { return m_Entities; };
        uint64_t GetNextEntity() { return m_NextEntity; };

    private:

        std::vector<uint64_t> m_Entities;
        std::vector<uint64_t> m_RemovedEntities;
        uint64_t m_NextEntity = 0;
    };
}