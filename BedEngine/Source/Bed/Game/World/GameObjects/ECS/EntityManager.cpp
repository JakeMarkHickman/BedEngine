#include "EntityManager.h"

#include <iostream>

uint64_t Bed::EntityManager::CreateEntity()
{
    uint64_t CreatedEntity;

    if(!m_RemovedEntities.empty()) //Check to see if there is any deleted entites
    {
        CreatedEntity = m_RemovedEntities.back();
        m_Entities.push_back(CreatedEntity);
        m_RemovedEntities.pop_back();

        return CreatedEntity;
    }

    m_Entities.push_back(m_NextEntity);
    CreatedEntity = m_NextEntity;
    m_NextEntity++;

    return CreatedEntity;
}

bool Bed::EntityManager::DestroyEntity(uint64_t entityToDestroy)
{
    for(size_t i = 0; i < m_Entities.size(); i++)
    {
        if(entityToDestroy == m_Entities[i])
        {
            m_RemovedEntities.push_back(entityToDestroy);
            m_Entities.erase(m_Entities.begin() + i); // because it needs a iterator for some reason
            return true;
        }
    }

    return false;
}