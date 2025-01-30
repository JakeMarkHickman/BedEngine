#pragma once

#include <typeindex>
#include <unordered_map>
#include <Tools/Memory/MemoryPool.h>
#include <vector>
#include <Bed/Singleton/Singleton.h>

//TODO: make sure this correctly cleans up

namespace Bed
{
    class BED_API ContextRegistry : public Bed::Singleton<ContextRegistry>
    {
    public:
        template<typename Context>
        void RegisterContext(Context contextToRegister)
        {
            std::type_index contextIndex = typeid(Context);

            if(IsContextRegistered(contextIndex))
            {
                //TODO: if context already exists add another one unless specified

                std::cout << "Context " << contextIndex.name() << " already exists" << "\n";
                return;
            }

            Bed::MemoryPool memoryPool(sizeof(Context), 1);
            void* memory = memoryPool.Allocate();

            if(!memory)
            {
                std::cout << "Unable to allocate memory to Context registry for context " << contextIndex.name() << "\n";
                return;
            }

            Context* contentPointer = new (memory) Context(contextToRegister);

            m_RegisteredContexts.emplace(contextIndex, std::move(memoryPool));
            m_Contexts.emplace(contextIndex, contentPointer);
        }

        template<typename Context>
        void RemoveContext()
        {
            std::type_index contextIndex = typeid(Context);

            if (!IsContextRegistered(contextIndex))
            {
                std::cout << "Context " << contextIndex.name() << " doesn't exist" << "\n";
                return;
            }

            void* contextPointer = m_Contexts[contextIndex];

            // Destroy the context object (call its destructor)

            if(contextPointer)
            {
                static_cast<Context*>(contextPointer)->~Context();
            }
            

            // The memory pool will be automatically cleaned up when it goes out of scope
            // Remove the context and memory pool from the maps
            m_Contexts.erase(contextIndex);
            m_RegisteredContexts.erase(contextIndex);
        }

        template<typename Context>
        Context* GetContext()
        {
            std::type_index contextIndex = typeid(Context);

            if(!IsContextRegistered(contextIndex))
            {
                std::cout << "Context " << contextIndex.name() << " doesn't exist" << "\n";
                return nullptr;
            }

            return static_cast<Context*>(m_Contexts[contextIndex]);
        }

    private:
        friend class Bed::Singleton<ContextRegistry>; //Allows private and protected access to Singleton class
        ContextRegistry() {}; //private decleration so no  more instanced

        bool IsContextRegistered(std::type_index context)
        {
            return m_RegisteredContexts.find(context) != m_RegisteredContexts.end();
        }

        std::unordered_map<std::type_index, Bed::MemoryPool> m_RegisteredContexts;
        std::unordered_map<std::type_index, void*> m_Contexts;
    };
}