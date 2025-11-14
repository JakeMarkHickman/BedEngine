#include "OpenShader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OpenDebugger.h"

#include <SleepTrace.h>

Bed::OpenShader::OpenShader(const std::string& filepath) : Bed::ShaderAsset(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ShaderAsset::ParseShader();
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Bed::OpenShader::~OpenShader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Bed::OpenShader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Bed::OpenShader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Bed::OpenShader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Bed::OpenShader::SetUniform2f(const std::string& name, Pillow::Vector2f value)
{
    GLCall(glUniform2f(GetUniformLocation(name), value.x, value.y));
}

void Bed::OpenShader::SetUniform3f(const std::string& name, Pillow::Vector3f value)
{
    GLCall(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
}

void Bed::OpenShader::SetUniform3f(const std::string& name, Bed::Colour3 value)
{
    GLCall(glUniform3f(GetUniformLocation(name), value.r, value.g, value.b));
}

void Bed::OpenShader::SetUniform4f(const std::string& name, Pillow::Vector4f value)
{
    GLCall(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
}

void Bed::OpenShader::SetUniform4f(const std::string& name, Bed::Colour4 value)
{
    GLCall(glUniform4f(GetUniformLocation(name), value.r, value.g, value.b, value.a));
}

void Bed::OpenShader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

/*void Bed::OpenShader::SetUniformMat4f(const std::string& name, const glm::mat4& Matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &Matrix[0][0]));
}*/

void Bed::OpenShader::SetUniform1iv(const std::string& name, int count, int* value)
{
    GLCall(glUniform1iv(GetUniformLocation(name), count, value));
}

int Bed::OpenShader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCashe.find(name) != m_UniformLocationCashe.end())
    {
        return m_UniformLocationCashe[name];
    }

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        LOG_WARN("Uniform ", name, " does not exist!");
    }

    m_UniformLocationCashe[name] = location;
    return location;
}

unsigned int Bed::OpenShader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char)); // alloca allocates memory to the stack instead of the heap
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::string shadertype = (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
        LOG_ERROR("Failed to compile " + shadertype + " shader! " + message);
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Bed::OpenShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    
    return program;
}