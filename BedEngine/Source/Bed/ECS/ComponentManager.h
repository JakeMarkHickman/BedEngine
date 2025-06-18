#pragma once

#include <Tools/Memory/SparseSet.h>
#include <Tools/Memory/MemoryPool.h>
#include <vector>
#include <typeindex>
#include <unordered_map>

namespace Bed
{
    class ComponentManager
    {
    public:
        //TODO: Look into archietypes
        //TODO: query system 
        //TODO: Make Pointers return const
        //TODO: Command Buffers

        template<typename Component>
        void AttachComponent(uint64_t entity, Component comp)
        {
            uint64_t hashCode = typeid(Component).hash_code();
            uint64_t compID;

            if(!IsComponentRegistered(hashCode))
            {
                compID = RegisterComponent(hashCode);

                //TODO: Align memory pools to a cashe line (64 bytes) if pool is full or would be cut off make a new pool!
                // MemoryPool needs to be constructed inside the vector as moving data causes a crash
                m_ComponentPool.emplace_back(sizeof(Component), 10001); //TODO: Scale this with the amount of entities available

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
                throw std::runtime_error("Component Pool is full!");
            }

            Component* allocatedComp = new (rawMemory) Component(comp);

            m_EntityComponents[compID].Insert(entity, allocatedComp);
        }

        template<typename Component>
        void RemoveComponent(uint64_t entity)
        {
            uint64_t hashCode = typeid(Component).hash_code();
            uint64_t compID;

            if(!IsComponentRegistered(hashCode) || !HasComponent<Component>(entity))
            {
                return;
            }

            compID = GetRegisteredComponentIndex(hashCode);

            void* compData = m_EntityComponents[compID].GetData(entity);

            if(compData)
            {
                // call the destructor of the data
                static_cast<Component*>(compData)->~Component();

                // Deallocate the memory from the pool
                m_ComponentPool[compID].Deallocate(compData);

                // Remove entity from sparse set
                m_EntityComponents[compID].Remove(entity);
            }
        }

        template<typename Component>
        bool HasComponent(uint64_t entity)
        {
            uint64_t hashCode = typeid(Component).hash_code();

            if(!IsComponentRegistered(hashCode))
            {
                return false;
            }

            uint64_t compID = GetRegisteredComponentIndex(hashCode);

            if(!m_EntityComponents[compID].HasIndex(entity))
            {
                return false;
            }
            return true;
        }

        template<typename Component>
        Component* GetComponent(uint64_t entity)
        {
            uint64_t hashCode = typeid(Component).hash_code();

            if(!IsComponentRegistered(hashCode))
            {
                return nullptr;
            }

            uint64_t compID = GetRegisteredComponentIndex(hashCode);

            return static_cast<Component*>(m_EntityComponents[compID].GetData(entity));
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