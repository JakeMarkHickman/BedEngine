#pragma once

#include <Bed/Core.h>

//TODO: OPERATORS FOR VECTORS!!!

namespace Bed
{
    struct BED_API Vector2
    {
        Vector2() {};
        Vector2(float value) : x(value), y(value) {};
        Vector2(float x, float y) : x(x), y(y) {};

        float x = 0.0f;
        float y = 0.0f;

        // Is Equal
        bool operator==(float scalar) const
        {
            return x == scalar && y == scalar;
        }
        bool operator==(const Vector2& other) const
        {
            return x == other.x && y == other.y;
        }

        // Is NOT Equal
        bool operator!=(float scalar) const
        {
            return x != scalar && y != scalar;
        }
        bool operator!=(const Vector2& other) const
        {
            return x != other.x && y != other.y;
        }
    };

    struct BED_API Vector3
    {
        Vector3() {};
        Vector3(float value) : x(value), y(value), z(value) {};
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // Is Equal
        bool operator==(float scalar) const
        {
            return x == scalar && y == scalar && z == scalar;
        }
        bool operator==(const Vector3& other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }

        // Is NOT Equal
        bool operator!=(float scalar) const
        {
            return x != scalar && y != scalar && z != scalar;
        }
        bool operator!=(const Vector3& other) const
        {
            return x != other.x && y != other.y && z != other.z;
        }

        // Plus and Equal
        Vector3& operator+=(float scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            return *this;
        }
        Vector3& operator+=(const Vector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        // Multiplication
        Vector3 operator*(float scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        Vector3 operator*(const Vector3& other) const
        {
            return Vector3(x * other.x, y * other.y, z * other.z);
        }
    };

    struct BED_API Vector4
    {
        Vector4() {};
        Vector4(float value) : x(value), y(value), z(value), w(value) {};
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        // Is Equal
        bool operator==(float scalar) const
        {
            return x == scalar && y == scalar && z == scalar && w == scalar;
        }
        bool operator==(const Vector4& other) const
        {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        // Is NOT Equal
        bool operator!=(float scalar) const
        {
            return x != scalar && y != scalar && z != scalar && w == scalar;
        }
        bool operator!=(const Vector4& other) const
        {
            return x != other.x && y != other.y && z != other.z && w != other.w;
        }
    };
}