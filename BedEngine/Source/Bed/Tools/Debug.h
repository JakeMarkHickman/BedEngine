#pragma once

#include <iostream>

namespace Bed
{
    class Debug
    {
    public:
        static void print()
        {
            std::cout << "This will be the log" << std::endl;
        }
    };
}