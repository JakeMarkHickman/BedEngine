#pragma once

namespace Bed
{
    template<typename T>
    class Singleton
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