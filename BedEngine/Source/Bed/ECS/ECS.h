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

        /*
            This adds a Component attched from a class
            For exmple:
            Bed::SpriteRenderer::OnSpriteComponentAttached;

            variable 1 - instance: this is the function where you are grabbing the function from I.E SpriteRenderer
            variable 3 - function: The function refrence I.E &Bed::SpriteRenderer::OnSpriteComponentAttached

            USE CASE:
            SpriteRenderer spriteRenderer;
            RegisterOnComponentAttachedGlobal(spriteRenderer, &Bed::SpriteRenderer::OnSpriteComponentAttached);
        */
        template<typename... Comps, typename T>
        void RegisterOnComponentAttachedGlobal(T& instance, void(T::*fn)(Bed::World&, uint64_t))
        {
            RegisterOnComponentAttachedGlobal<Comps...>([&instance, fn](Bed::World& world, uint64_t entity){(instance.*fn)(world, entity);});
        }

        template<typename... Comps>
        void RegisterOnComponentAttachedGlobal(std::function<void(Bed::World&, uint64_t)> listener)
        {
            ([&]{
                uint64_t hashCode = typeid(Comps).hash_code();
                m_GlobalComponentAttachedlisteners[hashCode].emplace_back(listener);
            }(), ...);
        }

        /*
            This adds a Component removed from a class
            For exmple:
            Bed::SpriteRenderer::OnSpriteComponentRemoved;

            variable 1 - instance: this is the function where you are grabbing the function from I.E SpriteRenderer
            variable 3 - function: The function refrence I.E &Bed::SpriteRenderer::OnSpriteComponentRemoved

            USE CASE:
            SpriteRenderer spriteRenderer;
            RegisterOnComponentRemovedGlobal(spriteRenderer, &Bed::SpriteRenderer::OnSpriteComponentRemoved);
        */
        template<typename... Comps, typename T>
        void RegisterOnComponentRemovedGlobal(T& instance, void(T::*fn)(Bed::World&, uint64_t))
        {
            RegisterOnComponentRemovedGlobal<Comps...>([&instance, fn](Bed::World& world, uint64_t entity){(instance.*fn)(world, entity);});
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

        /*
            This adds a system from a class
            For exmple:
            Bed::SpriteRenderer::SpriteSystem;

            variable 1 - instance: this is the function where you are grabbing the function from I.E SpriteRenderer
            variable 2 - worldID: The world that this function will be active on
            variable 3 - function: The function refrence I.E &Bed::SpriteRenderer::SpriteSystem

            USE CASE:
            SpriteRenderer spriteRenderer;
            uin64_t world1 = CreateWorld();
            AddSystem(spriteRenderer, world1, &Bed::SpriteRenderer::SpriteSystem);
        */
        template<typename T>
        void AddSystem(T& instance, uint64_t worldID, void(T::*fn)(Bed::World&))
        {
            AddSystem(worldID, [&instance, fn](Bed::World& world){(instance.*fn)(world);});
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