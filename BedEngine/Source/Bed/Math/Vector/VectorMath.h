#pragma once

#include <Vector/VectorMath.h>

namespace Bed
{
    class VectorMath
    {
    public:
        static float Magnitude(const Bed::Vector2& v)
        {
            return std::sqrt(v.x * v.x + v.y * v.y);
        };

        static float Magnitude( const Bed::Vector4& v )
        {
            return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        };

        static Bed::Vector2 Normalise( const Bed::Vector2& v )
        {
            float mag = Magnitude(v);

            float x = isnan(v.x/mag) ? 0.0f : v.x/mag;
            float y = isnan(v.y/mag) ? 0.0f : v.y/mag;

            return Bed::Vector2(x, y);
        };

        static Bed::Vector4 Normalise( const Bed::Vector4& v )
        {
            float mag = Magnitude(v);

            float x = isnan(v.x/mag) ? 0.0f : v.x/mag;
            float y = isnan(v.y/mag) ? 0.0f : v.y/mag;
            float z = isnan(v.z/mag) ? 0.0f : v.z/mag;
            float w = isnan(v.w/mag) ? 0.0f : v.w/mag;

            return Bed::Vector4(x, y, z, w);
        };
    };
}