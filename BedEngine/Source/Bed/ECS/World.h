#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"

#include <PhysicsWorld.h>
#include <functional>

namespace Bed
{
    class World
    {
    public:
        Mattress::PhysicsWorld GetWorldPhysics() { return m_Physics; };

        //Entities
        uint64_t CreateEntity();
        void DestroyEntity(uint64_t entity);
        std::vector<uint64_t> GetAllEntities() { return m_EntityManager.GetAllEntities(); };

        //Components
        template<typename... Components>
        void AttachComponents(uint64_t entity, Components... comps)
        {
            ([&]{
                m_ComponentManager.AttachComponent(entity, comps);
            }(), ...);
        }

        template<typename... Components>
        void RemoveComponents(uint64_t entity)
        {
            ([&]{
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
        Bed::EntityManager m_EntityManager;
        Bed::ComponentManager m_ComponentManager;

        Mattress::PhysicsWorld m_Physics;

        std::vector<std::function<void(Bed::World&)>> m_Systems;
    };
}