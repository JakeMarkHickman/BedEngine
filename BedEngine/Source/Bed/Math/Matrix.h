#pragma once

//TODO figure this shit out??
#include "Matrix/Matrix2x2.h"

namespace Bed
{
    struct Matrix3x3
    {
        Matrix3x3()
        {
            //create Identity matrix
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    element[i][j] = (i == j) ? 1.0f : 0.0f; 
                }
            }
        };
        
        float element[3][3];

        Matrix3x3 operator*(float scalar)
        {
            Matrix3x3 value;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    value.element[i][j] *= scalar;
                }
            }
            return value;
        }
    };

    struct Matrix4x4
    {
        Matrix4x4();

        float element[4][4];
    };
    
}
