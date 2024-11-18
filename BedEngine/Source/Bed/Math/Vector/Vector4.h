#pragma once

#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Vector4
    {
        Vector4() {};
        Vector4(float value) : x(value), y(value), z(value), w(value) {};
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
        Vector4(const Vector4& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {};

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
            return x != scalar && y != scalar && z != scalar && w != scalar;
        }
        bool operator!=(const Vector4& other) const
        {
            return x != other.x && y != other.y && z != other.z && w != other.w;
        }

        // Is Greater than or Equal
        bool operator>=(float scalar) const
        {
            return x >= scalar && y >= scalar && z >= scalar && w >= scalar;
        }
        bool operator>=(const Vector4& other) const
        {
            return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
        }

        // Is Less than or Equal
        bool operator<=(float scalar) const
        {
            return x <= scalar && y <= scalar && z <= scalar && w <= scalar;
        }
        bool operator<=(const Vector4& other) const
        {
            return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
        }

        // Is Greater than
        bool operator>(float scalar) const
        {
            return x > scalar && y > scalar && z > scalar && w > scalar;
        }
        bool operator>(const Vector4& other) const
        {
            return x > other.x && y > other.y && z > other.z && w > other.w;
        }

        // Is Less than
        bool operator<(float scalar) const
        {
            return x < scalar && y < scalar && z < scalar && w < scalar;
        }
        bool operator<(const Vector4& other) const
        {
            return x < other.x && y < other.y && z < other.z && w < other.w;
        }

        // Multiply and Equal
        Vector4& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }
        Vector4& operator*=(const Vector4& other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }

        // Divide and Equal
        Vector4& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }
        Vector4& operator/=(const Vector4& other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return *this;
        }

        // Plus and Equal
        Vector4& operator+=(float scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            w += scalar;
            return *this;
        }
        Vector4& operator+=(const Vector4& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }

        // Subtract and Equal
        Vector4& operator-=(float scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            w -= scalar;
            return *this;
        }
        Vector4& operator-=(const Vector4& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }

        // Multiplication
        Vector4 operator*(float scalar) const
        {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }
        Vector4 operator*(const Vector4& other) const
        {
            return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        //Division
        Vector4 operator/(float scalar) const 
        {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }
        Vector4 operator/(const Vector4& other) const
        {
            return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
        }

        // Addition
        Vector4 operator+(float scalar) const
        {
            return Vector4(x + scalar, y + scalar, z + scalar, w + scalar);
        }
        Vector4 operator+(const Vector4& other) const
        {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        // Subtraction
        Vector4 operator-(float scalar) const 
        {
            return Vector4(x - scalar, y - scalar, z - scalar, w - scalar);
        }
        Vector4 operator-(const Vector4& other) const
        {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }
    };
}