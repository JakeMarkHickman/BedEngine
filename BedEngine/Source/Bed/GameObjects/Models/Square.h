#pragma once

namespace Bed
{

    //TODO: Make this use 3 Dimensions

    float Positions[] = 
    {
    //   X      Y
        -0.5f, -0.5f, 0.0f, 0.0f,   // 0
        -0.5f,  0.5f, 0.0f, 1.0f,   // 1
         0.5f,  0.5f, 1.0f, 1.0f,   // 2
         0.5f, -0.5f, 1.0f, 0.0f    // 3
    };

    unsigned int Indices[]
    {
        0, 1, 2,
        0, 2, 3
    };
}