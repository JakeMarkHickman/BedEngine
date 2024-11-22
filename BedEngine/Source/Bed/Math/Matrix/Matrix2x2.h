#pragma once

#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Matrix2x2
    {
        Matrix2x2()
        {
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    element[i][j] = (i == j) ? 1.0f : 0.0f;
                }
            }
        }
            
        float element[2][2];

        Matrix2x2 operator*(float scalar)
        {
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    element[i][j] *= scalar;
                }
            }
        }
    };
}