#pragma once

#include "OpenGL/OpenShader.h"

// TODO: Make this file able to be used with diffrent Renderers

namespace Bed
{
    class BED_API Shader
    {
    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        unsigned int GetRendererID() { return m_OpenShader->GetRendererID(); };

        // set uniforms
        void SetUniform1f(const std::string& name, float value);
        void SetUniform3f(const std::string& name, Bed::Vector3 value);
        void SetUniform4f(const std::string& name, Bed::Vector4 value);
        void SetUniform1i(const std::string& name, int value);
        void SetUniformMat4f(const std::string& name, const glm::mat4& Matrix);

        // set array uniforms
        void SetUniform1iv(const std::string& name, int count, int* value);

    private:
        OpenShader* m_OpenShader;
    };
}