#pragma once

#include <Math/Vector.h>
#include <Math/Colour.h>
#include <string>
#include <unordered_set>

// TODO: replace GLM Includes
#include <glm.hpp>

// TODO: Make this file able to be used with diffrent Renderers
// TODO: BMP has easier reading than PNG and JPEG

namespace Bed
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class ShaderAsset
    {
    public:
        ShaderAsset(std::string path) : m_FilePath(path) {};

        virtual void Bind() const {};
        virtual void Unbind() const {};

        virtual unsigned int GetRendererID() { return -1; };

        // set uniforms
        virtual void SetUniform1f(const std::string& name, float value) {};
        virtual void SetUniform2f(const std::string& name, Bed::Vector2 value) {};
        virtual void SetUniform3f(const std::string& name, Pillow::Vector3f value) {};
        virtual void SetUniform3f(const std::string& name, Bed::Colour3 value) {};
        virtual void SetUniform4f(const std::string& name, Bed::Vector4 value) {};
        virtual void SetUniform4f(const std::string& name, Bed::Colour4 value) {};

        virtual void SetUniform1i(const std::string& name, int value) {};

        virtual void SetUniformMat4f(const std::string& name, const glm::mat4& Matrix) {};

        // set array uniforms
        virtual void SetUniform1iv(const std::string& name, int count, int* value) {};
    
    protected:
        std::string m_FilePath;

        Bed::ShaderProgramSource ParseShader();
    
    private:
        std::string ImplmentIncludes(std::string path, std::unordered_set<std::string> includes);      
    };
}