#pragma once

#include <Bed/Core.h>

//TODO: Make this compatable with Colour

namespace Bed
{
    struct Vector2
    {
        Vector2() {};
        Vector2(float value) : x(value), y(value) {};
        Vector2(float x, float y) : x(x), y(y) {};
        Vector2(const Vector2& vector) : x(vector.x), y(vector.y) {};

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

        // Is Greater than or Equal
        bool operator>=(float scalar) const
        {
            return x >= scalar && y >= scalar;
        }
        bool operator>=(const Vector2& other) const
        {
            return x >= other.x && y >= other.y;
        }

        // Is Less than or Equal
        bool operator<=(float scalar) const
        {
            return x <= scalar && y <= scalar;
        }
        bool operator<=(const Vector2& other) const
        {
            return x <= other.x && y <= other.y;
        }

        // Is Greater than
        bool operator>(float scalar) const
        {
            return x > scalar && y > scalar;
        }
        bool operator>(const Vector2& other) const
        {
            return x > other.x && y > other.y;
        }

        // Is Less than
        bool operator<(float scalar) const
        {
            return x < scalar && y < scalar;
        }
        bool operator<(const Vector2& other) const
        {
            return x < other.x && y < other.y;
        }

        // Multiply and Equal
        Vector2& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        Vector2& operator*=(const Vector2& other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        // Divide and Equal
        Vector2& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }
        Vector2& operator/=(const Vector2& other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        // Plus and Equal
        Vector2& operator+=(float scalar)
        {
            x += scalar;
            y += scalar;
            return *this;
        }
        Vector2& operator+=(const Vector2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        // Subtract and Equal
        Vector2& operator-=(float scalar)
        {
            x -= scalar;
            y -= scalar;
            return *this;
        }
        Vector2& operator-=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // Multiplication
        Vector2 operator*(float scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }
        Vector2 operator*(const Vector2& other) const
        {
            return Vector2(x * other.x, y * other.y);
        }

        //Division
        Vector2 operator/(float scalar) const 
        {
            return Vector2(x / scalar, y / scalar);
        }
        Vector2 operator/(const Vector2& other) const
        {
            return Vector2(x / other.x, y / other.y);
        }

        // Addition
        Vector2 operator+(float scalar) const
        {
            return Vector2(x + scalar, y + scalar);
        }
        Vector2 operator+(const Vector2& other) const
        {
            return Vector2(x + other.x, y + other.y);
        }

        // Subtraction
        Vector2 operator-(float scalar) const 
        {
            return Vector2(x - scalar, y - scalar);
        }
        Vector2 operator-(const Vector2& other) const
        {
            return Vector2(x - other.x, y - other.y);
        }
    };
}