#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Bed::Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(); //TODO: Change this to install Dir
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Bed::Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Bed::Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Bed::Shader::Unbind() const
{
    glUseProgram(0);
}

void Bed::Shader::SetUniform4f(const std::string& name, Bed::Vector4 value)
{
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Bed::Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Bed::Shader::SetUniformMat4f(const std::string& name, const glm::mat4& Matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &Matrix[0][0]);
}

int Bed::Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCashe.find(name) != m_UniformLocationCashe.end())
    {
        return m_UniformLocationCashe[name];
    }

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cout << "Warning: Uniform " << name << " doesn't exist!" << std::endl;
    }

    m_UniformLocationCashe[name] = location;
    return location;
}

unsigned int Bed::Shader::CompileShader(unsigned int type, const std::string& source)
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

unsigned int Bed::Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

Bed::ShaderProgramSource Bed::Shader::ParseShader()
{
    std::ifstream stream(m_FilePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}