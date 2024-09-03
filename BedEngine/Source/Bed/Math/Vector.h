#pragma once

namespace Bed
{
    struct Vector2
    {
        Vector2(float x, float y) : x(x), y(y) {};
        float x;
        float y;
    };

    struct Vector3
    {
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
        float x;
        float y;
        float z;
    };

    struct Vector4
    {
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
        float x;
        float y;
        float z;
        float w;
    };
}