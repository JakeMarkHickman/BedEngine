#include "RenderableObject.h"

void Quilt::RenderableManager::CreateRenderableObject(uint64_t entityID, RenderableObject object)
{
    m_EntityLink.Insert(entityID, object);

}

Quilt::RenderableObject& Quilt::RenderableManager::GetRenderableObject(uint64_t entityID)
{
    return m_EntityLink.GetData(entityID);
}