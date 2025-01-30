#pragma once

namespace Bed
{
    template<typename T>
    class BED_API Singleton
    {
    public:
        static T& GetInstance()
        {
            static T instance;

            return instance;
        }

        Singleton(Singleton const&) = delete;
        void operator=(Singleton const&) = delete;

    protected:
        Singleton() {};
    };
}