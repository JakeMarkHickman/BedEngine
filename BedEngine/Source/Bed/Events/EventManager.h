#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <Tools/Memory/MemoryPool.h>
#include <Bed/Events/Event.h>

//TODO: sort this out later when it becomes more important

namespace Bed
{
    class EventManager
    {
    public:
        //TODO: implement in a simular fashion to how ECS was implemented with components

        template <typename Payload>
        void CreateEvent(const std::string& eventName, int listnerAmmount) //TODO: make listners infinite
        {
            if(IsEventRegistered(eventName))
            {
                throw std::runtime_error("Event: " + eventName + " already exists");
            }

            RegisterEvent<Payload>(eventName, listnerAmmount);
        };

        template <typename Payload>
        void Subscribe(const std::string& eventName, std::function<void(Payload)> listner)
        {
            if(!IsEventRegistered(eventName)) // throw error if event doesnt exist
                throw std::runtime_error("Event: " + eventName + " doesnt exist");

            if(m_RegisteredEvents[eventName] != typeid(Payload).hash_code()) // Throw error if event payload doesnt match
                throw std::runtime_error("Event: " + eventName + " uses a diffrent data type");

            m_Listeners[eventName].emplace_back([listner](void* eventData) {listner(*static_cast<Payload*>(eventData)); });
        }

        template <typename Payload>
        void Broadcast(const std::string& eventName, Payload payload)
        {
            if(!IsEventRegistered(eventName))
                throw std::runtime_error("Event: " + eventName + " doesnt exist");

            if(m_RegisteredEvents[eventName] != typeid(Payload).hash_code())
                throw std::runtime_error("Event: " + eventName + " uses a diffrent data type");

            for(auto& listener : m_Listeners[eventName])
            {
                listener(&payload);
            }

            //Deallocation of event to not waste memory
            m_EventPools[eventName].Deallocate(&payload);
        }



    private:
    //TODO: Not completely done
        template<typename Payload>
        void RegisterEvent(const std::string& eventName, int poolSize)
        {
            uint64_t data = typeid(Payload).hash_code();
            m_RegisteredEvents.insert({ eventName, data });

            m_EventPool.insert({ eventName, Bed::MemoryPool(sizeof(Payload), poolSize)});
        };

        bool IsEventRegistered(const std::string& eventName)
        {
            return m_RegisteredEvents.find(eventName) != m_RegisteredEvents.end();
        };

        std::unordered_map<std::string, uint64_t> m_RegisteredEvents; // Make sure payload matches Event payload
        std::unordered_map<std::string, Bed::MemoryPool> m_EventPool;
        std::unordered_map<std::string, std::vector<std::function<void(void*)>>> m_Listeners;
    };
}