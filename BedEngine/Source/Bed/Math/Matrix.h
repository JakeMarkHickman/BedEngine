#pragma once

namespace Bed
{
    struct Matrix2
    {
        Matrix2();

        float element[2][2];
    };

    struct Matrix3
    {
        Matrix3();
        
        float element[3][3];

        Matrix3 operator*(float scalar)
        {
            for(int i = 0; i < 3; i++)
            {
                
            }
        }
    };

    struct Matrix4
    {
        Matrix4();

        float element[4][4];
    };
    
}
