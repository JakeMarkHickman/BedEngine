#pragma once

#include <string>
#include <Bed/Math/Vector.h>
#include <unordered_map>

// TODO: replace GLM Includes
#include <glm.hpp>

// TODO: Make this file able to be used with diffrent Renderers

namespace Bed
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class Shader
    {
    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // set uniforms
        void SetUniform4f(const std::string& name, Bed::Vector4 value);
        void SetUniform1i(const std::string& name, int value);
        void SetUniformMat4f(const std::string& name, const glm::mat4& Matrix);

    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        std::unordered_map<std::string, int> m_UniformLocationCashe;


        int GetUniformLocation(const std::string& name);

        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderProgramSource ParseShader();
    };
}