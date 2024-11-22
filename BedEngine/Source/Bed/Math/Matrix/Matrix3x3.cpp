#include "Matrix3x3.h"

Bed::Matrix3x3::Matrix3x3()
{
    //create Identity matrix
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            element[i][j] = (i == j) ? 1.0f : 0.0f; 
        }
    }
}