#pragma once

#include "../PillowCore.h"

namespace Pillow
{
    class Spherical
    {
    public:
        template<Floating T>
        static T WarpOnAxis(T coordinate, T strength)
        {
            return std::sin(strength * coordinate);
        }

        template<Floating T>
        static T GetDistance()
        {
            
        }
    };
}