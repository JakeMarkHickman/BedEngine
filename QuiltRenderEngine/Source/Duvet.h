#pragma once

#include <vector>

#include <SleepTrace.h>

#include "OpenGl/OpenDebugger.h"
#include "Mesh.h"
#include "Coverlet.h"
#include "Comforter.h"
#include "Texture.h"
#include "Vertex.h"
#include "Camera.h"

#include <Transform.h>

namespace Quilt
{
    class Duvet
    {
    public:
        static unsigned int CreateMesh(const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices, const Pillow::Transform* transform);
        static void RemoveMesh(unsigned int& meshHandle);

        static unsigned int CreateCamera(const Pillow::Transform* transform, bool isActive, float xScreenPos, float yScreenPos, float xScreenSize, float yScreenSize);
        static void RemoveCamera(unsigned int& cameraHandle);

        static void CreateTexture(const std::string texturePath, const TextureFiltering filter, unsigned int& meshHandle);

        static void SetViewPort(int width, int height) { WindowWidth = width; WindowHeight = height; };

        static bool IsContextValid();
        //Draw all registered meshes to the screen
        static void Draw();
        //Clears the screen from previous draw call
        static void Clear();

    private:
        inline static Quilt::Coverlet m_ShaderManager;
        inline static Quilt::Comforter m_BatchManager;
        inline static Quilt::BufferManager m_BufferManager;
        inline static Quilt::MeshManager m_MeshManager;
        inline static Quilt::TextureManager m_TextureManager;

        inline static Quilt::CameraManager m_CameraManager;

        inline static int WindowWidth = 0;
        inline static int WindowHeight = 0;
    };

    using Renderer = Duvet;
}