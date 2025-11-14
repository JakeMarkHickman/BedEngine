#pragma once

#include <string>
#include <Transform.h>

namespace Quilt
{
    //TODO: Remove this
    struct ShaderProgram
    {
        unsigned int Handle;
        unsigned int VertexShader;
        unsigned int FragmentShader;
    };

    class Coverlet
    {
    public:
        unsigned int AddShader(const std::string& VertexShader, const std::string& FragmentShader);


        void SetUniformMat4f(unsigned int handle, const std::string& name, const glm::mat4& data);


        void SetUniform1iv(unsigned int handle, const std::string& name, int count, int* value);
    private:
    
        bool isCompiledShader() { return false; };
        unsigned int GetShader() { return 0; };

        unsigned int CompileShader() { return 0; };

        //TODO: Store maps of hash codes of Program, vertex and fragment shader so no recopiles of shaders are needed
    };

    using Shader = Coverlet;
}