#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//TEMP
unsigned int VertexArrayObject;
unsigned int Shader;
unsigned int Buffer;
unsigned int IndexBufferObject;
float Positions[] = 
{
//   X      Y
    -0.5f, -0.5f,   // 0
    -0.5f,  0.5f,   // 1
     0.5f,  0.5f,   // 2
     0.5f, -0.5f    // 3
};

unsigned int Indices[]
{
    0, 1, 2,
    0, 2, 3
};

//TEMP