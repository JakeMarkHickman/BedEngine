#pragma once

#include <Bed/Core.h>

//TODO: Make this compatable with Colour

namespace Bed
{
    struct BED_API Vector3
    {
        Vector3() {};
        Vector3(float value) : x(value), y(value), z(value) {};
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
        Vector3(const Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {};

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

        // Is Greater than or Equal
        bool operator>=(float scalar) const
        {
            return x >= scalar && y >= scalar && z >= scalar;
        }
        bool operator>=(const Vector3& other) const
        {
            return x >= other.x && y >= other.y && z >= other.z;
        }

        // Is Less than or Equal
        bool operator<=(float scalar) const
        {
            return x <= scalar && y <= scalar && z <= scalar;
        }
        bool operator<=(const Vector3& other) const
        {
            return x <= other.x && y <= other.y && z <= other.z;
        }

        // Is Greater than
        bool operator>(float scalar) const
        {
            return x > scalar && y > scalar && z > scalar;
        }
        bool operator>(const Vector3& other) const
        {
            return x > other.x && y > other.y && z > other.z;
        }

        // Is Less than
        bool operator<(float scalar) const
        {
            return x < scalar && y < scalar && z < scalar;
        }
        bool operator<(const Vector3& other) const
        {
            return x < other.x && y < other.y && z < other.z;
        }

        // Multiply and Equal
        Vector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Vector3& operator*=(const Vector3& other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        // Divide and Equal
        Vector3& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }
        Vector3& operator/=(const Vector3& other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
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

        // Subtract and Equal
        Vector3& operator-=(float scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            return *this;
        }
        Vector3& operator-=(const Vector3& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
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

        //Division
        Vector3 operator/(float scalar) const 
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }
        Vector3 operator/(const Vector3& other) const
        {
            return Vector3(x / other.x, y / other.y, z / other.z);
        }

        // Addition
        Vector3 operator+(float scalar) const
        {
            return Vector3(x + scalar, y + scalar, z + scalar);
        }
        Vector3 operator+(const Vector3& other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        // Subtraction
        Vector3 operator-(float scalar) const 
        {
            return Vector3(x - scalar, y - scalar, z - scalar);
        }
        Vector3 operator-(const Vector3& other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
    };
}