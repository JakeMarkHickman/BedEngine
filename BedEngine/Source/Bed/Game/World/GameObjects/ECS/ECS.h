#pragma once

#include <vector>
#include <typeindex>
#include <memory>
#include <any>
#include <unordered_map>
#include <Bed/Tools/SparseSet.h>
#include <Bed/Core.h>

namespace Bed
{
    class BED_API ECS;

    using SystemFunc = void (*)(ECS&, float);

    class BED_API ECS
    {
    public:
        ECS() {};
        ~ECS() {};

        /////////////////////////////////////
        //              ENTITY             //
        /////////////////////////////////////

        std::vector<uint64_t> GetAllEntities() { return m_Entities; };

        uint64_t GetEntityAtIndex(uint64_t index) { return m_Entities.at(index); }

        uint64_t CreateEntity();

        void RemoveEntity(uint64_t entityToRemove);


        /////////////////////////////////////
        //             COMPONENT           //
        /////////////////////////////////////

        SparseSet<SparseSet<std::any>> GetEntityComponents() { return m_EntityComponents; }

        //Add Component(s) to an Entity
        template<typename... Components>
        void AttachComponents(uint64_t entity, const Components&... comp)
        {
            ([&] {
                uint64_t typeHash = typeid(comp).hash_code(); // Gets the Hash code of the data parsed for the sparse set
                uint64_t CompID;

                if(!IsRegisteredComponent(typeHash)) // Checks if Hash code is registered
                {
                    CompID = RegisterComponent(typeHash); // Register the component

                    Bed::SparseSet<std::any> newCompSet; // Create a new sparse set
                    newCompSet.Insert(entity, std::any(comp)); // populate the new sparse set

                    m_EntityComponents.Insert(CompID, newCompSet); // add the new set to the already existing one
                }
                else
                {
                    CompID = GetComponentIndex(typeHash); // Get Compindex from Hash Code

                    m_EntityComponents.GetData(CompID).Insert(entity, std::any(comp)); // Get data
                }
            }(), ...);
        }

        //Remove Component(s) from an Entity
        template<typename... Components>
        void RemoveComponents(uint64_t entity, Components... comp)
        {
            ([&] {
                //do things
            }(), ...);
        }

        template<typename... Components>
        bool HasComponents(uint64_t entity)
        {
            bool result = true;
            ([&] {
                uint64_t typeHash = typeid(Components).hash_code();

                if(!IsRegisteredComponent(typeHash))
                {
                    result = false;
                }
                else
                {
                    //TODO: Check for component on entity
                    uint64_t compID = GetComponentIndex(typeHash);

                    if(!m_EntityComponents.GetData(compID).HasIndex(entity))
                    {
                        result = false;
                    }
                }
            }(), ...);
            return result;
        }

        template<typename Component>
        Component GetComponent(uint64_t entity)
        {
            uint64_t typeHash = typeid(Component).hash_code();

            if(!IsRegisteredComponent(typeHash))
            {
                
            }

            uint64_t compID = GetComponentIndex(typeHash);

            try
            {
                return std::any_cast<Component>(m_EntityComponents.GetData(compID).GetData(entity));
            }
            catch (const std::bad_any_cast& e)
            {
                // Handle the case where the cast fails (e.g., wrong type)
                // Maybe log an error or throw an exception?
                // ...
                // For now, let's return a default-constructed Component:
                
            }
        }

        template<typename Component>
        void SetComponent(uint64_t entity, const Component& comp)
        {
            uint64_t typeHash = typeid(Component).hash_code();
            uint64_t compID = GetComponentIndex(typeHash);

            m_EntityComponents.GetData(compID).SetData(entity, comp);
        }

        /////////////////////////////////////
        //             SYSTEMS             //
        /////////////////////////////////////

        void UpdateSystems(float DeltaTime)
        {
            for(SystemFunc& Func : m_Systems)
            {
                Func(*this, DeltaTime);
            }
        };

        void AddSystem(SystemFunc System)
        {
            m_Systems.push_back(System);
        }

    private:

        uint64_t RegisterComponent(uint64_t hashCode)
        {
            uint64_t compID = m_NextComponent;

            m_RegisteredComponents.insert({hashCode, compID});

            m_NextComponent++;

            return compID;
        }

        bool IsRegisteredComponent(uint64_t hashCode)
        {
            return m_RegisteredComponents.find(hashCode) != m_RegisteredComponents.end();
        }

        uint64_t GetComponentIndex(uint64_t hashCode)
        {
            return m_RegisteredComponents.at(hashCode);
        }

        std::vector<uint64_t> m_Entities;
        uint64_t m_NextEntity = 0;

        std::unordered_map<uint64_t, uint64_t> m_RegisteredComponents;
        uint64_t m_NextComponent = 0;

        SparseSet<SparseSet<std::any>> m_EntityComponents;

        std::vector<SystemFunc> m_Systems;
    };
}