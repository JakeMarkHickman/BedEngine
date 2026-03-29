#pragma once

#include <vector>

#include <SleepTrace.h>

#include "OpenGl/OpenDebugger.h"
#include "Mesh.h"
#include "Shader.h"
#include "Batch.h"
#include "Texture.h"
#include "Vertex.h"
#include "Camera.h"
#include "RenderableObject.h"

#include <Transform.h>

namespace Quilt
{
    class Duvet
    {
    public:
        static void Init();

        static unsigned int CreateShader(std::string shaderName, std::string vertexShader, std::string fragmentShader);
        static unsigned int GetShader(std::string shaderName);

        static void SetDefaultTexture(const std::string& path);
        static unsigned int GetDefaultTexture();

        static unsigned int CreateMesh(const std::string& name, const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices);
        static unsigned int CreateMesh(const std::string& path);

        static void CreateRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID, const Pillow::Transform* transform);

        static void RemoveMesh(unsigned int& meshHandle);

        static unsigned int CreateCamera(const Pillow::Transform* transform, bool isActive, float xScreenPos, float yScreenPos, float xScreenSize, float yScreenSize);
        static void RemoveCamera(unsigned int& cameraHandle);

        static void CreateTexture(const std::string texturePath, const TextureFiltering filter, uint64_t entityID);

        static void SetViewPort(int width, int height) { WindowWidth = width; WindowHeight = height; };

        static bool IsContextValid();
        //Draw all registered meshes to the screen
        static void Draw();
        //Clears the screen from previous draw call
        static void Clear();

    private:
        inline static Quilt::ShaderManager m_ShaderManager;
        inline static Quilt::BatchManager m_BatchManager;
        inline static Quilt::BufferManager m_BufferManager;
        inline static Quilt::MeshManager m_MeshManager;
        inline static Quilt::TextureManager m_TextureManager;

        inline static Quilt::CameraManager m_CameraManager;

        inline static Quilt::RenderableManager m_RenderManager;

        inline static std::unordered_map<std::string, unsigned int> m_ShaderLookup;

        inline static int WindowWidth = 0;
        inline static int WindowHeight = 0;

        inline static unsigned int m_DefaultTextureID = 0;
    };

    using Renderer = Duvet;
}