#pragma once

#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Vector2
    {
        Vector2(float x, float y) : x(x), y(y) {};
        float x;
        float y;
    };

    struct BED_API Vector3
    {
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
        float x;
        float y;
        float z;

        // Operator overload for scalar multiplication
        Vector3 operator*(float scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        // Operator overload for vector addition
        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        // Optional: For ease of use, you might want to implement this too
        Vector3& operator+=(const Vector3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
    };

    struct BED_API Vector4
    {
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
        float x;
        float y;
        float z;
        float w;
    };
}