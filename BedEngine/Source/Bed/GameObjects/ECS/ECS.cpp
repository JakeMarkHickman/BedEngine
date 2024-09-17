#include "ECS.h"

uint64_t Bed::ECS::CreateEntity()
{
    uint64_t entity = m_NextEntity; // Create an entity from the next entity
    m_Entities.push_back(entity); // push the created entity into the vector

    m_NextEntity++; // increment the next entity counter

    return entity; // return the created entity
}

void Bed::ECS::RemoveEntity(uint64_t entityToRemove)
{
    m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entityToRemove), m_Entities.end());
}