#pragma once

#include <GL/glew.h>
#include <SleepTrace.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        LOG_ERROR("[OpenGl Error] (" + std::to_string(error) + "): " + function + " " + file + ":" + std::to_string(line) );
        return false;
    }
    return true;
}
