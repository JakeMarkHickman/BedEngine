#pragma once

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
            
        }

    private:


    }
}