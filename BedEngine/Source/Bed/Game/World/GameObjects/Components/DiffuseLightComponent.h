#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct DiffuseLight
    {
        DiffuseLight(Bed::Vector3 colour) : Colour(colour) {};

        Bed::Vector3 Colour;
    };
}