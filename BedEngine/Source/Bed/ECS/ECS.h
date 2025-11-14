#pragma once

#include "World.h"
#include "unordered_map"

#include <Tools/Memory/MemoryPool.h>
#include <functional>

namespace Bed
{
    //TODO: this needs cleaning up there is alot of indirection

    /*  
        TODO:

            Create World from template:
                This loads a world from JSON

            Create Entity from template:
                This loads an entity from Json

            Component Sets:
                Create a component set which will have defualt data 
                such as:

                RegisterComponentSet("name", DATA);

                uint64_t entity = UseComponentSet("name");

            Config to Systems:
                Adds configuration to systems
                such as:

                .Multithreaded = true;
                .Priority = 3;
                ect

            Query System

            Events or Hooks that fire with Attaching/removing components, entities created/removed, Worlds created/Removed ect

            Large Refactor now that GradEx is done!
    */
    class ECS
    {
    public:
        ECS() { m_WorldPool = new Bed::MemoryPool(sizeof(Bed::World), 10); };
        ~ECS() {};

        std::unordered_map<uint64_t, Bed::World*>& GetActiveWorlds() { return m_WorldRegistry; };

        template<typename... Comps>
        void RegisterOnComponentAttachedGlobal(std::function<void(Bed::World&, uint64_t)> listener)
        {
            ([&]{
                uint64_t hashCode = typeid(Comps).hash_code();
                m_GlobalComponentAttachedlisteners[hashCode].emplace_back(listener);
            }(), ...);
        }

        template<typename... Comps>
        void RegisterOnComponentRemovedGlobal(std::function<void(Bed::World&, uint64_t)> listener)
        {
            ([&]{
                uint64_t hashCode = typeid(Comps).hash_code();
                m_GlobalComponentRemovedlisteners[hashCode].emplace_back(listener);
            }(), ...);
        }
        
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

        std::unordered_map<uint64_t, std::vector<std::function<void(Bed::World&, uint64_t)>>> m_GlobalComponentAttachedlisteners;
        std::unordered_map<uint64_t, std::vector<std::function<void(Bed::World&, uint64_t)>>> m_GlobalComponentRemovedlisteners;
    };
}