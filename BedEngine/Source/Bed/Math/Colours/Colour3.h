#pragma once

namespace Bed
{
    struct Colour3
    {
        Colour3();
        Colour3(float value) : r(value), g(value), b(value) {};
        Colour3(float red, float green, float blue) : r(red), g(green), b(blue) {};

        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
    }
}