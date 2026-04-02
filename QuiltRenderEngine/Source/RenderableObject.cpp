#include "RenderableObject.h"

void Quilt::RenderableManager::CreateRenderableObject(uint64_t entityID, RenderableObject object)
{
    m_EntityLink.Insert(entityID, object);
}

bool Quilt::RenderableManager::HasRenderableObject(uint64_t entityID)
{
    return m_EntityLink.HasIndex(entityID);
}

void Quilt::RenderableManager::RemoveRenderableObject(uint64_t entityID)
{
    m_EntityLink.Remove(entityID);
}

Quilt::RenderableObject& Quilt::RenderableManager::GetRenderableObject(uint64_t entityID)
{
    return m_EntityLink.GetData(entityID);
}

uint64_t Quilt::RenderableManager::GetLastRenderableEntity()
{
    unsigned int size = m_EntityLink.GetIDs().back();
    return m_EntityLink.GetIDs()[size];
}