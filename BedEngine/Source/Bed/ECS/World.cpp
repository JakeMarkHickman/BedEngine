#include "World.h"

uint64_t Bed::World::CreateEntity()
{
    return m_EntityManager.CreateEntity();
}

void Bed::World::DestroyEntity(uint64_t entity)
{
    m_EntityManager.DestroyEntity(entity);
}


void Bed::World::AddSystem(std::function<void(Bed::World&)> systemToAdd)
{
    m_Systems.push_back(systemToAdd);
}

void Bed::World::RemoveSystem(std::function<void(Bed::World&)> systemToRemove)
{

}

void Bed::World::RemoveAllSystems()
{
    m_Systems.clear();
}

void Bed::World::UpdateSystems()
{
    for(std::function<void(Bed::World&)> system : m_Systems)
    {
        system(*this);
    }
}