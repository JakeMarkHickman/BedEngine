#include "ComponentManager.h"

uint64_t Bed::ComponentManager::RegisterComponent(uint64_t componentHashCode)
{
    uint64_t RegisteredComp = m_RegisteredComponents;

    m_ComponentRegisty.insert({componentHashCode, RegisteredComp});
    m_RegisteredComponents++;

    return RegisteredComp;
}

bool Bed::ComponentManager::IsComponentRegistered(uint64_t componentHashCode)
{
    return m_ComponentRegisty.find(componentHashCode) != m_ComponentRegisty.end();
}

uint64_t Bed::ComponentManager::GetRegisteredComponentIndex(uint64_t componentHashCode)
{
    return m_ComponentRegisty.at(componentHashCode);
}