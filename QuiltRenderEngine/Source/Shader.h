#pragma once

#include <string>
#include <Transform.h>
#include <unordered_map>

#include <vector>

namespace Quilt
{
    //TODO: Remove this
    struct ShaderProgram
    {
        unsigned int Handle;
        unsigned int VertexShader;
        unsigned int FragmentShader;
    };

    struct Shaders
    {
        std::vector<unsigned int> Programs;
        std::vector<unsigned int> VertexShaders;
        std::vector<unsigned int> FragmentShaders;
    };

    class Coverlet
    {
    public:
        unsigned int AddShader(const std::string& VertexShader, const std::string& FragmentShader);
        unsigned int GetShaderProgram(const std::string& VertexShader, const std::string& FragmentShader);
        bool IsShaderProgram(const std::string& VertexShader, const std::string& FragmentShader);

        void SetUniformMat4f(unsigned int handle, const std::string& name, const glm::mat4& data);


        void SetUniform1iv(unsigned int handle, const std::string& name, int count, int* value);
    private:

    
        bool isCompiledShader() { return false; };
        unsigned int GetShader() { return 0; };

        unsigned int CompileShader() { return 0; };

        //TODO: Store maps of hash codes of Program, vertex and fragment shader so no recopiles of shaders are needed
        std::unordered_map<uint64_t, unsigned int> m_ExistingShaderPrograms;
    };

    using ShaderManager = Coverlet;
}