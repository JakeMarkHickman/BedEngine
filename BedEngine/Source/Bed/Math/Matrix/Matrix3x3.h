#pragma once

#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Matrix3x3
    {
        Matrix3x3();
        
        float element[3][3];

        //Multiplication
        Matrix3x3 operator*(float scalar) const
        {
            Matrix3x3 value;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    value.element[i][j] = element[i][j] * scalar;
                }
            }
            return value;
        }

        //Addition
        Matrix3x3 operator+(const Matrix3x3& other) const
        {
            Matrix3x3 value;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    value.element[i][j] = element[i][j] + other.element[i][j];
                }
            }
            return value;
        }

        //Subtraction
        Matrix3x3 operator-(const Matrix3x3& other) const
        {
            Matrix3x3 value;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    value.element[i][j] = element[i][j] - other.element[i][j];
                }
            }
            return value;
        }
    };
}
