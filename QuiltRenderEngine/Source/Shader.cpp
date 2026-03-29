#include "Shader.h"

//TODO: this needs to go
#include "OpenGl/OpenDebugger.h"
#include <functional>

unsigned int Quilt::Coverlet::AddShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    //TODO: Check if VertexShader or FragmentShader already exists and reuse it as it doesnt need to be recompiled

    unsigned int handle;

    unsigned int vertexShader;
    unsigned int fragmentShader;

    handle = glCreateProgram();

    //Vertex Shader
    unsigned int vertid = glCreateShader(GL_VERTEX_SHADER);

    const char* vertSrc = VertexShader.c_str();

    GLCall(glShaderSource(vertid, 1, &vertSrc, nullptr));
    GLCall(glCompileShader(vertid));

    int vertresult;
    GLCall(glGetShaderiv(vertid, GL_COMPILE_STATUS, &vertresult));
    if (vertresult == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(vertid, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char)); // alloca allocates memory to the stack instead of the heap
        GLCall(glGetShaderInfoLog(vertid, length, &length, message));
        LOG_ERROR("Failed to compile Vertex shader! ", message);
        GLCall(glDeleteShader(vertid));
    }
    vertexShader = vertid;

    //Fragment shader
    unsigned int fragid = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragSrc = FragmentShader.c_str();

    GLCall(glShaderSource(fragid, 1, &fragSrc, nullptr));
    GLCall(glCompileShader(fragid));

    int fragresult;
    GLCall(glGetShaderiv(fragid, GL_COMPILE_STATUS, &fragresult));
    if (fragresult == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(fragid, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char)); // alloca allocates memory to the stack instead of the heap
        GLCall(glGetShaderInfoLog(fragid, length, &length, message));
        LOG_ERROR("Failed to compile Fragment shader! ", message);
        GLCall(glDeleteShader(fragid));
    }
    fragmentShader = fragid;

    GLCall(glAttachShader(handle, vertexShader));
    GLCall(glAttachShader(handle, fragmentShader));

    GLCall(glLinkProgram(handle));
    GLCall(glValidateProgram(handle));

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

    uint64_t shaderHashCode = std::hash<std::string>{}(VertexShader + FragmentShader);

    m_ExistingShaderPrograms.emplace(shaderHashCode, handle);

    return handle;
}

unsigned int Quilt::Coverlet::GetShaderProgram(const std::string& VertexShader, const std::string& FragmentShader)
{
    uint64_t shaderHashCode = std::hash<std::string>{}(VertexShader + FragmentShader);

    return m_ExistingShaderPrograms.at(shaderHashCode);
}

bool Quilt::Coverlet::IsShaderProgram(const std::string& VertexShader, const std::string& FragmentShader)
{
    uint64_t shaderHashCode = std::hash<std::string>{}(VertexShader + FragmentShader);

    return m_ExistingShaderPrograms.find(shaderHashCode) != m_ExistingShaderPrograms.end();
}

void Quilt::Coverlet::SetUniformMat4f(unsigned int handle, const std::string& name, const glm::mat4& Matrix)
{
    GLCall(glUniformMatrix4fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE, &Matrix[0][0]));
}

void Quilt::Coverlet::SetUniform1iv(unsigned int handle, const std::string& name, int count, int* value)
{
    GLCall(glUniform1iv(glGetUniformLocation(handle, name.c_str()), count, value));
}