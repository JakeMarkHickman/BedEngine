#pragma once

#include <string>
#include <unordered_map>

#include <Graphics/ShaderAsset.h>

namespace Bed
{
    class OpenShader : public Bed::ShaderAsset
    {
    public:
        OpenShader(const std::string& filepath);
        ~OpenShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual unsigned int GetRendererID() override { return m_RendererID; };

        // set uniforms
        virtual void SetUniform1f(const std::string& name, float value) override;
        virtual void SetUniform2f(const std::string& name, Bed::Vector2 value) override;
        virtual void SetUniform3f(const std::string& name, Pillow::Vector3f value) override;
        virtual void SetUniform3f(const std::string& name, Bed::Colour3 value) override;
        virtual void SetUniform4f(const std::string& name, Bed::Vector4 value) override;
        virtual void SetUniform4f(const std::string& name, Bed::Colour4 value) override;

        virtual void SetUniform1i(const std::string& name, int value) override;

        virtual void SetUniformMat4f(const std::string& name, const glm::mat4& Matrix) override;

        // set array uniforms
        virtual void SetUniform1iv(const std::string& name, int count, int* value) override;

    private:
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCashe;


        int GetUniformLocation(const std::string& name);

        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    };
}