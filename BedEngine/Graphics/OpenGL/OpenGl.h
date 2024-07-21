#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//TEMP
    unsigned int buffer;
    float positions[6] = 
    {
    //   X      Y
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };
//TEMP


#ifdef BED_WINDOWS_PLATFORM

    GLFWwindow* window;

    bool OpenGLCreateWindow(int width, int height, const char* title)
    {
        if(!glfwInit())
        {
            return false;
        }

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);

        if(glewInit() != GLEW_OK)
        {
            return false;
        }

        //TEMP
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2 /*2 represents the number of dimensions so 3 would be 3D*/, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        glEnableVertexAttribArray(0);
        //TEMP

        return true;
    }

    void OpenGLUpdateWindow()
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);


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
#endif