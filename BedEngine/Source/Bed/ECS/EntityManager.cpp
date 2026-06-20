#include "EntityManager.h"

#include <SleepTrace.h>

uint64_t Bed::EntityManager::CreateEntity()
{
    uint64_t CreatedEntity;

    if(!m_RemovedEntities.empty()) //Check to see if there is any deleted entites
    {
        CreatedEntity = m_RemovedEntities.back();
        LOG_INFO("Reusing Entity: ", CreatedEntity);
        m_Entities.push_back(CreatedEntity);
        m_RemovedEntities.pop_back();

        return CreatedEntity;
    }
    m_Entities.push_back(m_NextEntity);
    CreatedEntity = m_NextEntity;

    LOG_INFO("Creating Entity ", CreatedEntity);

    m_NextEntity++;

    return CreatedEntity;
}

bool Bed::EntityManager::DestroyEntity(uint64_t entityToDestroy)
{
    auto entityLocation = std::find(m_Entities.begin(), m_Entities.end(), entityToDestroy);
    if(entityLocation != m_Entities.end())
    {
        *entityLocation = m_Entities.back();
        m_Entities.pop_back();
        m_RemovedEntities.push_back(entityToDestroy);
        return true;
    }

    LOG_WARN("Entity ", entityToDestroy, " not found");
    return false;
}