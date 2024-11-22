#pragma once

#include <string>
#include <Math/Vector.h>
#include <unordered_map>
#include <Bed/Core.h>

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

    class OpenShader
    {
    public:
        OpenShader(const std::string& filepath);
        ~OpenShader();

        void Bind();
        void Unbind();

        unsigned int GetRendererID() { return m_RendererID; };

        // set uniforms
        void SetUniform4f(const std::string& name, Bed::Vector4 value);
        void SetUniform1i(const std::string& name, int value);
        void SetUniformMat4f(const std::string& name, const glm::mat4& Matrix);

        // set array uniforms
        void SetUniform1iv(const std::string& name, int count, int* value);

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