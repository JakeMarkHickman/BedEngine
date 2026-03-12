#include "ECS.h"

uint64_t Bed::ECS::CreateWorld()
{
    uint64_t worldID = m_NextId++;

    void* rawMemory = m_WorldPool->Allocate();
    if (!rawMemory)
    {
        LOG_FATAL("Component pool is full!");
    }

    Bed::World* allocatedWorld = new (rawMemory) Bed::World();


    m_WorldRegistry.emplace(worldID, allocatedWorld);


    for(auto& listeners : m_GlobalComponentAttachedlisteners)
    {
        for(auto& listener : listeners.second)
        {
            m_WorldRegistry[worldID]->RegisterOnComponentAttached(listeners.first, listener);
        }
    }

    for(auto& listeners : m_GlobalComponentRemovedlisteners)
    {
        for(auto& listener : listeners.second)
        {
            m_WorldRegistry[worldID]->RegisterOnComponentRemoved(listeners.first, listener);
        }
    }

    for(std::function<void(Bed::World&)> system : m_GlobalSystems)
    {
        m_WorldRegistry[worldID]->AddSystem(system);
    }

    return worldID;
}

void Bed::ECS::RemoveWorld(uint64_t worldID)
{
    //TODO: create remove world
}

uint64_t Bed::ECS::CreateEntity(uint64_t worldID)
{
    return m_WorldRegistry[worldID]->CreateEntity();
}

void Bed::ECS::DestroyEntity(uint64_t worldID, uint64_t entityID)
{
    m_WorldRegistry[worldID]->DestroyEntity(entityID);
}

void Bed::ECS::AddSystemGlobal(std::function<void(Bed::World&)> systemToAdd)
{
    m_GlobalSystems.emplace_back(systemToAdd);
}

void Bed::ECS::AddSystem(uint64_t worldID, std::function<void(Bed::World&)> systemToAdd)
{
    m_WorldRegistry[worldID]->AddSystem(systemToAdd);
}

void Bed::ECS::RemoveSystem(uint64_t worldID, std::function<void(Bed::World&)> systemToRemove)
{
    m_WorldRegistry[worldID]->RemoveSystem(systemToRemove);
}

void Bed::ECS::RemoveAllSystems(uint64_t worldID)
{
    m_WorldRegistry[worldID]->RemoveAllSystems();
}

void Bed::ECS::UpdateSystems()
{
    for(int i = 0; i < m_WorldRegistry.size(); i++)
    {
        m_WorldRegistry[i]->UpdateSystems();
    }
}
