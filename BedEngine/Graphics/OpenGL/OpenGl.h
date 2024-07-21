#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

void OpenGLCreateWindow(int width, int height, const char* title)
{
    if(!glfwInit())
    {
        return;
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        return;
    }
}

void OpenGLUpdateWindow()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

bool OpenGLIsWindowOpen()
{
    return !glfwWindowShouldClose(window);
}

void OpenGLCloseWindow()
{
    glfwTerminate();
}