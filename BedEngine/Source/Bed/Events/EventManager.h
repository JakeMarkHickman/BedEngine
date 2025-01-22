#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <Tools/Memory/MemoryPool.h>
#include <Bed/Events/Event.h>

namespace Bed
{
    class EventManager
    {
    public:
        //TODO: implement in a simular fashion to how ECS was implemented with components

        template <typename payload>
        Event<payload>* CreateEvent(const std::string& eventName) 
        {
            if(!IsEventRegistered(eventName))
            {

            }

            return nullptr;
        };



    private:
    //TODO: Not completely done
        template<typename payload>
        void RegisterEvent()
        {
            std::type_index payloadTypeIndex = std::type_index(payload)
        };

        bool IsEventRegistered(std::string eventName)
        {
            return m_RegisteredEvents.find(eventName) != m_RegisteredEvents.end();
        };

        std::unordered_map<std::string, std::type_index> m_RegisteredEvents;
        std::unordered_map<std::type_index, Bed::MemoryPool> m_EventPool;
        std::unordered_map<std::type_index, std::vector<std::function<void(void*)>>> m_Listeners;
    };
}