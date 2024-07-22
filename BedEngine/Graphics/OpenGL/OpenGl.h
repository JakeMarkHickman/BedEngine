#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

//TEMP
unsigned int shader;
unsigned int buffer;
float positions[6] = 
{
//   X      Y
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
};
//TEMP

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); // alloca allocates memory to the stack instead of the heap
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile "<< (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")  <<" Shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

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

        std::string vertexShader = 
            "#version 330 core\n"
            ""
            "layout(location = 0) in vec4 position;"
            ""
            "void main()"
            "{"
            "   gl_Position = position;"
            "}";

        std::string fragmentShader = 
            "#version 330 core\n"
            ""
            "layout(location = 0) out vec4 colour;"
            ""
            "void main()"
            "{"
            "   colour = vec4(0.651, 0.086, 0.902, 1.0);"
            "}";

        shader = CreateShader(vertexShader, fragmentShader);
        glUseProgram(shader);
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
        glDeleteProgram(shader);
        glfwTerminate();
    }
#endif

