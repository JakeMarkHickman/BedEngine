#pragma once

#include "../PillowCore.h"

namespace Pillow
{
    //TODO: analytical formulas to speed up distance calculation

    class Hyperbolic
    {
    public:
        /*
            Convert a world axis into Hyperbolic space
        */
        template<Floating T>
        static T WarpOnAxis(T coordinate, T strength)
        {
            return std::tanh(strength * coordinate);
        }

        template<Floating T>
        static T GetDistance(T coordinate1, T coordinate2, T strength)
        {
            const int step = 100;
            T h = (coordinate2 - coordinate1) / step;
            T sum = 0;
            for (int i = 0; i <= step; i++)
            {
                T x = coordinate1 + i * h;
                T weight = (i == 0 || i == step) ? 0.5 : 1;
                sum += weight * std::sqrt(MetricCoefficient(x, strength));
            }

            return h * sum;
        }

    private:
        template<Floating T>
        static T MetricCoefficient(T coordinate, T strength)
        {
            T strengthcoord = strength * coordinate;
            T sech_strengthcoord = 1 / std::cosh(strengthcoord);
            return strength * strength * sech_strengthcoord * sech_strengthcoord;
        }
    };
}