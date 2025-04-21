#pragma once

//TODO: Make this used through out the engine and compatable with vector

namespace Bed
{
    struct Colour3
    {
        Colour3() {};
        Colour3(float value) : r(value), g(value), b(value) {};
        Colour3(float red, float green, float blue) : r(red), g(green), b(blue) {};
        Colour3(const Colour3& colour) : r(colour.r), g(colour.g), b(colour.b) {};

        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
    };
}