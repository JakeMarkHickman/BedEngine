#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include <Bed/Core.h>

namespace Bed
{
    class ECS;

    using SystemFunc = void (*)(ECS&, float);

    class BED_API ECS
    {
    public:
        ECS() {};
        ~ECS() {};

        /////////////////////////////////////
        //              ENTITY             //
        /////////////////////////////////////

        uint64_t CreateEntity()
        {
            return m_EntityManager.CreateEntity();
        }

        std::vector<uint64_t> GetAllEntities()
        {
            return m_EntityManager.GetAllEntities();
        }
        


        /////////////////////////////////////
        //             COMPONENT           //
        /////////////////////////////////////

        //TODO: This causes a break on exeption when on more than 1000 entites
        template<typename... Components>
        void AttachComponents(uint64_t entity, Components... comps)
        {
            ([&]{
                m_CompManager.AttachComponent(entity, comps);
            }(), ...);
        }

        template<typename... Components>
        void RemoveComponents(uint64_t entity)
        {
            ([&]{
                m_CompManager.RemoveComponent<Components>(entity);
            }(), ...);
        }

        template<typename... Components>
        bool HasComponents(uint64_t entity)
        {
            bool result = true;
            ([&]{
                if(!m_CompManager.HasComponent<Components>(entity))
                {
                    result = false;
                }
            }(), ...);

            return result;
        }

        template<typename Component>
        Component* GetComponent(uint64_t entity)
        {
            return m_CompManager.GetComponent<Component>(entity);
        }

        /////////////////////////////////////
        //             SYSTEMS             //
        /////////////////////////////////////

        void AddSystem(SystemFunc systemToAdd)
        {
            //TODO: check for pre-existing systems
            m_Systems.push_back(systemToAdd);
        };

        void RemoveSystem(SystemFunc systemToRemove)
        {
            //TODO: check to see if system exists
            // no need to delete function pointer
        };

        void RemoveAllSystems()
        {
            m_Systems.clear();
        };

        void UpdateSystems(float DeltaTime)
        {
            for(SystemFunc& Syst : m_Systems)
            {
                Syst(*this, DeltaTime);
            }
        };

    private:

        Bed::EntityManager m_EntityManager;
        Bed::ComponentManager m_CompManager;
        std::vector<SystemFunc> m_Systems;
    };
}