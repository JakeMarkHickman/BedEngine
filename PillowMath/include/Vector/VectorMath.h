#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>

#include "../PillowCore.h"

namespace Pillow
{
    class VectorMath
    {
    public:
        template<Arithmetic T>
        static float Magnitude( const Pillow::Vector2<T>& v)
        {
            return std::sqrt(v.x * v.x + v.y * v.y);
        };

        template<Arithmetic T>
        static float Magnitude( const Pillow::Vector3<T>& v )
        {
            return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        };

        template<Arithmetic T>
        static Pillow::Vector2<float> Normalise( const Pillow::Vector2<T>& v)
        {
            float mag = Magnitude(v);

            float x = isnan(v.x/mag) ? 0.0f : v.x/mag;
            float y = isnan(v.x/mag) ? 0.0f : v.y/mag;

            return Pillow::Vector2<float>(x, y);
        }

        template<Arithmetic T>
        static Pillow::Vector3<float> Normalise( const Pillow::Vector3<T>& v)
        {
            float mag = Magnitude(v);

            float x = isnan(v.x/mag) ? 0.0f : v.x/mag;
            float y = isnan(v.y/mag) ? 0.0f : v.y/mag;
            float z = isnan(v.z/mag) ? 0.0f : v.z/mag;

            return Pillow::Vector3<float>(x, y, z);
        };
    };
}