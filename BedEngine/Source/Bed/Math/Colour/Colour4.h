#pragma once

namespace Bed
{
    struct Colour4
    {
        Colour4() {};
        Colour4(float value) : r(value), g(value), b(value), a(value) {};
        Colour4(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) {};

        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
    }
}