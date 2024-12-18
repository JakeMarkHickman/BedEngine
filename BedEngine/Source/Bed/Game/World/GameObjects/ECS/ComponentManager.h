#pragma once

#include <Tools/Memory/SparseSet.h>
#include <Tools/Memory/MemoryPool.h>
#include <vector>
#include <typeindex>
#include <memory>
#include <unordered_map>

namespace Bed
{
    class ComponentManager
    {
    public:

        /*~ComponentManager()
        {
            for(auto& sparse : m_EntityComponents)
            {
                sparse.Clear();
            }

            m_EntityComponents.clear();

            for(auto& pool : m_ComponentPool)
            {
                pool.~MemoryPool();
            }

            //m_ComponentPool.clear();
        }*/

        template<typename Component>
        void AttachComponent(uint64_t entity, Component comp)
        {
            uint64_t hashCode = typeid(Component).hash_code();
            uint64_t compID;

            if(!IsComponentRegistered(hashCode))
            {
                compID = RegisterComponent(hashCode);

                // MemoryPool needs to be constructed inside the vector as moving data causes a crash
                m_ComponentPool.emplace_back(sizeof(Component), 1000); //TODO: Scale this with the amount of entities available

                Bed::SparseSet<void*> newCompSet;
                m_EntityComponents.emplace_back(newCompSet); 
            }
            else
            {
                compID = GetRegisteredComponentIndex(hashCode);
            }

            void* rawMemory = m_ComponentPool[compID].Allocate();

            if(!rawMemory)
            {
                throw std::runtime_error("ComponentPool is full!");
            }

            Component* allocatedComp = new (rawMemory) Component(comp);

            m_EntityComponents[compID].Insert(entity, allocatedComp);
        }

        template<typename Component>
        void RemoveComponent(uint64_t entity)
        {

        }

        template<typename Component>
        bool HasComponent(uint64_t entity)
        {

        }

    private:
        uint64_t RegisterComponent(uint64_t componentHashCode);
        bool IsComponentRegistered(uint64_t componentHashCode);
        uint64_t GetRegisteredComponentIndex(uint64_t componentHashCode);

        std::unordered_map<uint64_t, uint64_t> m_ComponentRegisty;
        std::vector<Bed::MemoryPool> m_ComponentPool;
        std::vector<Bed::SparseSet<void*>> m_EntityComponents;
        uint64_t m_RegisteredComponents = 0;

    };
}