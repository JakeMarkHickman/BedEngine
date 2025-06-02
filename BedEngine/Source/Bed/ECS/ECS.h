#pragma once

#include "World.h"
#include "unordered_map"

#include <Tools/Memory/MemoryPool.h>

namespace Bed
{
    class ECS
    {
    public:
        ECS() { m_WorldPool = new Bed::MemoryPool(sizeof(Bed::World), 10); };
        ~ECS() {};

        uint64_t CreateWorld();
        void RemoveWorld(uint64_t worldID);

        uint64_t CreateEntity(uint64_t worldID);
        void DestroyEntity(uint64_t worldID, uint64_t entityID);

        template<typename... Components>
        void AttachComponents(uint64_t worldID, uint64_t entityID, Components... comps)
        {
            m_WorldRegistry[worldID]->AttachComponents(entityID, std::forward<Components>(comps)...);
        }

        void AddSystem(uint64_t worldID, std::function<void(Bed::World&)> systemToAdd);
        void RemoveSystem(uint64_t worldID, std::function<void(Bed::World&)> systemToRemove);
        void RemoveAllSystems(uint64_t worldID);
        void UpdateSystems();

    private:

        std::unordered_map<uint64_t, Bed::World*> m_WorldRegistry;
        Bed::MemoryPool* m_WorldPool;
        int64_t m_NextId = 0;
    };
}