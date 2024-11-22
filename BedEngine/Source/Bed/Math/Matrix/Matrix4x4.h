#pragma once

#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Matrix4x4
    {
        Matrix4x4()
        {
            //create Identity matrix
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    element[i][j] = (i == j) ? 1.0f : 0.0f; 
                }
            }
        };
        
        float element[4][4];

        Matrix4x4 operator*(float scalar)
        {
            Matrix4x4 value;
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    value.element[i][j] *= scalar;
                }
            }
            return value;
        }
    };
}