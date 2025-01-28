#pragma once

#include <typeindex>
#include <unordered_map>
#include <Tools/Memory/MemoryPool.h>

namespace Bed
{
    class ContextRegistry
    {
    public:
        template<typename Context>
        void RegisterContext(Context& contextToRegister)
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

            new (memory) Context(contextToRegister);

            m_RegisteredContexts.emplace(contextIndex, std::move(memoryPool));
        }

        template<typename Context>
        void RemoveContext()
        {

        }

        template<typename Context>
        Context* GetContext()
        {
            return nullptr;
        }

    private:

        bool IsContextRegistered(std::type_index context)
        {
            return m_RegisteredContexts.find(context) != m_RegisteredContexts.end();
        }

        std::unordered_map<std::type_index, Bed::MemoryPool> m_RegisteredContexts;
    };
}