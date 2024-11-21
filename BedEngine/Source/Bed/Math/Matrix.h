#pragma once

//TODO figure this shit out??

namespace Bed
{
    struct Matrix2x2
    {
        Matrix2x2();

        float element[2][2];
    };

    struct Matrix3x3
    {
        Matrix3x3();
        
        float element[3][3];

        Matrix3x3 operator*(float scalar)
        {
            Matrix3x3 value;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {

                }
            }
        }
    };

    struct Matrix4x4
    {
        Matrix4x4();

        float element[4][4];
    };
    
}
