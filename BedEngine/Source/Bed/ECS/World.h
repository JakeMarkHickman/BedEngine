#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"

#include <PhysicsWorld.h>
#include <TuftingWorld.h>
#include <SleepTrace.h>
#include <unordered_map>
#include <functional>

namespace Bed
{
    class World
    {
    public:
        Mattress::PhysicsWorld& GetWorldPhysics() { return m_Physics; };

        //TODO: Finish the event system for entities and components. After this document and move onto hooking in physics and renderering

        //Entities
        /*
            Register a function to when OnEntityCreated() gets fired.
            E.G.

            void testFunc(Bed::World world, uint64_t entity)
            {
                //Do Something
            }

            RegisterOnEntityCreated(testFunc);

        */
        //void RegisterOnEntityCreated(std::function<void(Bed::World&, uint64_t)> listener);

        /*
            Register a function to when OnEntityDestroyed() gets fired.
            E.G.

            void testFunc(Bed::World world, uint64_t entity)
            {
                //Do Something
            }

            RegisterOnEntityDestroyed(testFunc);
        */
        //void RegisterOnEntityDestroyed(std::function<void(Bed::World&, uint64_t)> listener)

        /*
            Creates an entity
        */
        uint64_t CreateEntity();

        /*
            Destroy an entity

            Removes all components.
        */
        void DestroyEntity(uint64_t entity);

        /*
            Gets all entities within the world
        */
        std::vector<uint64_t>& GetAllEntities() { return m_EntityManager.GetAllEntities(); };

        //Components
        /*

        */
        template<typename... Comps>
        void RegisterOnComponentAttached(std::function<void(Bed::World&, uint64_t)> listener)
        {
            ([&]{
                uint64_t hashCode = typeid(Comps).hash_code();

                m_ComponentAttachedlisteners[hashCode].emplace_back(listener);
            }(), ...);
        }

        void RegisterOnComponentAttached(uint64_t hashCode, std::function<void(Bed::World&, uint64_t)> listener)
        {
            m_ComponentAttachedlisteners[hashCode].emplace_back(listener);
        }

        template<typename... Comps>
        void RegisterOnComponentRemoved(std::function<void(Bed::World&, uint64_t)> listener)
        {
            ([&]{
                uint64_t hashCode = typeid(Comps).hash_code();
                m_ComponentAttachedlisteners[hashCode].emplace_back(listener);
            }(), ...);
        }

        void RegisterOnComponentRemoved(uint64_t hashCode, std::function<void(Bed::World&, uint64_t)> listener)
        {
            m_ComponentRemovedlisteners[hashCode].emplace_back(listener);
        }

        template<typename... Components>
        void AttachComponents(uint64_t entity, Components... comps)
        {
            ([&]{
                m_ComponentManager.AttachComponent(entity, comps);
                uint64_t hashCode = typeid(comps).hash_code();
                OnComponentAttached(entity, hashCode);
            }(), ...);
        }

        template<typename... Components>
        void RemoveComponents(uint64_t entity)
        {
            ([&]{
                uint64_t hashCode = typeid(Components).hash_code();
                OnComponentRemoved(entity, hashCode);
                m_ComponentManager.RemoveComponent<Components>(entity);
            }(), ...);
        }

        template<typename... Components>
        bool HasComponents(uint64_t entity)
        {
            bool result = true;
            ([&]{
                if(!m_ComponentManager.HasComponent<Components>(entity))
                {
                    result = false;
                }
            }(), ...);
            return result;
        }

        template<typename Component>
        Component* GetComponent(uint64_t entity)
        {
            return m_ComponentManager.GetComponent<Component>(entity);
        }

        //Systems
        void AddSystem(std::function<void(Bed::World&)> systemToAdd);
        void RemoveSystem(std::function<void(Bed::World&)> systemToRemove);
        void RemoveAllSystems();
        void UpdateSystems();

    private:

        //Entity
        /*
            OnEntityCreated() gets fired after an entity has been created
        */
        void OnEntityCreated(uint64_t entityID) {};

        /*
            OnEntityDestroyed() gets fired after an entity has been destroyed
        */
        void OnEntityDestroyed(uint64_t entityID) {};

        //Components
        /*

        */
        void OnComponentAttached(uint64_t entityID, uint64_t componentHashCode)
        {
            if(m_ComponentAttachedlisteners.find(componentHashCode) != m_ComponentAttachedlisteners.end())
            {
                for(std::function<void(Bed::World&, uint64_t)> event : m_ComponentAttachedlisteners[componentHashCode])
                {
                    event(*this, entityID);
                }
            }
        }

        void OnComponentRemoved(uint64_t entityID, uint64_t componentHashCode)
        {
            if(m_ComponentRemovedlisteners.find(componentHashCode) != m_ComponentRemovedlisteners.end())
            {
                for(std::function<void(Bed::World&, uint64_t)> event : m_ComponentRemovedlisteners[componentHashCode])
                {
                    event(*this, entityID);
                }
            }
        }

        //Managers
        Bed::EntityManager m_EntityManager;
        Bed::ComponentManager m_ComponentManager;

        //TODO: Remove these
        Mattress::PhysicsWorld m_Physics;
        Mattress::TuftingWorld m_PhysicsWorld;

        //Systems
        std::vector<std::function<void(Bed::World&)>> m_Systems;

        //Events
        std::unordered_map<uint64_t, std::vector<std::function<void(Bed::World&, uint64_t)>>> m_ComponentAttachedlisteners;
        std::unordered_map<uint64_t, std::vector<std::function<void(Bed::World&, uint64_t)>>> m_ComponentRemovedlisteners;
        std::vector<std::function<void(Bed::World&, uint64_t)>> m_EntityCreatedlisteners;
        std::vector<std::function<void(Bed::World&, uint64_t)>> m_EntityDestroyedlisteners;
    };
}