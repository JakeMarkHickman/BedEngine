#include "Shader.h"

#include <iostream>

#include "OpenGL/OpenDebugger.h"

Bed::Shader::Shader(const std::string& filepath)
{
    m_OpenShader = new OpenShader(filepath);
}

Bed::Shader::~Shader()
{
    delete m_OpenShader;
    m_OpenShader = nullptr;
}

void Bed::Shader::Bind() const
{
    if(m_OpenShader)
    {
        std::cout << "Shader Bind Function" << std::endl;
        m_OpenShader->Bind();
    }
}

void Bed::Shader::Unbind() const
{
    m_OpenShader->Unbind();
}

void Bed::Shader::SetUniform4f(const std::string& name, Bed::Vector4 value)
{
    m_OpenShader->SetUniform4f(name, value);
}

void Bed::Shader::SetUniform1i(const std::string& name, int value)
{
    m_OpenShader->SetUniform1i(name, value);
}

void Bed::Shader::SetUniformMat4f(const std::string& name, const glm::mat4& Matrix)
{
    m_OpenShader->SetUniformMat4f(name, Matrix);
}

void Bed::Shader::SetUniform1iv(const std::string& name, int count, int* value)
{
    m_OpenShader->SetUniform1iv(name, count, value);
}