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
#include "VertexArray.h"

#include <Transform.h>

namespace Quilt
{
    struct SpriteInstanceData
    {
        glm::mat4 TransfomMatrix;
        Pillow::Vector4f Colour;
        Pillow::Vector2f UVMin;
        Pillow::Vector2f UVMax;
        float TextureID;
        float padding1;
        float padding2;
        float padding3;
    };

    struct InstanceUpload
    {
        unsigned int InstanceBufferHandle;
        unsigned int Slot;
        std::vector<uint8_t> Data;
    };

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

        static void CreateRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID);
        static void UpdateSpriteInstanceData(uint64_t entityID, Pillow::Transform& transform, Pillow::Vector4f& colour, Pillow::Vector2f& textureCoords, float& textureID);
        static void UpdateTransform(uint64_t entityID, Pillow::Transform& transform);
        static void RemoveRenderableObject(uint64_t entityID);

        static unsigned int CreateCamera(bool isActive, float xScreenPos, float yScreenPos, float xScreenSize, float yScreenSize);
        static void UpdateCamera(unsigned int cameraHandle, Pillow::Transform& trnasform);
        static void RemoveCamera(unsigned int& cameraHandle);

        static int CreateTexture(uint64_t entityID, const std::string texturePath, const TextureFiltering filter);
        static int RegisterTexture(const std::string texturePath, Quilt::TextureFiltering filter) { return m_TextureManager.AddTexture(texturePath, filter); };
        static int GetTexture(const std::string texturePath) { return m_TextureManager.GetTexture(texturePath); };
        static bool IsRegisteredTexture(const std::string texturePath) { return m_TextureManager.IsTextureAssigned(texturePath); };

        static void SetViewPort(int width, int height) { m_CameraManager.SetWindowWidth(width); m_CameraManager.SetWindowHeight(height); };

        template<typename T>
        static void QueueInstance(unsigned int entityID, const T& data)
        {
            RenderableObject& object = m_RenderManager.GetRenderableObject(entityID);
            Batch& batch = m_BatchManager.GetBatch(object.BatchID);

            QueueInstanceData(batch.InstanceBufferHandle, object.InstanceSlot, &data, sizeof(T));
        }

        //Check if linked context is valid like OpenGL
        static bool IsContextValid();
        //Flush the Instance Queue to the GPU
        static void FlushInstanceDataQueue() 
        { 
            for(const InstanceUpload& command: m_InstanceUploadQueue)
            {
                m_BufferManager.PopulateBuffer(command.InstanceBufferHandle, command.Data.data(), 1, command.Slot);
            }
            m_InstanceUploadQueue.clear();
        };
        //Draw all registered meshes to the screen
        static void Draw();
        //Clears the screen from previous draw call
        static void Clear();

    private:

        static void CreateDynamicRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID);
        static void CreateInstancedRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID);

        static void QueueInstanceData(unsigned int instanceBufferHandle, unsigned int slot, const void* data, size_t size) 
        {
            InstanceUpload command;
            command.InstanceBufferHandle = instanceBufferHandle;
            command.Slot = slot;
            command.Data.assign(static_cast<const uint8_t*>(data), static_cast<const uint8_t*>(data) + size);

            m_InstanceUploadQueue.push_back(command);
        };

        inline static Quilt::VertexArrayManager m_VertexArrayManager;

        inline static Quilt::ShaderManager m_ShaderManager;
        inline static Quilt::BatchManager m_BatchManager;
        inline static Quilt::BufferManager m_BufferManager;
        inline static Quilt::MeshManager m_MeshManager;
        inline static Quilt::TextureManager m_TextureManager;

        inline static Quilt::CameraManager m_CameraManager;

        inline static Quilt::RenderableManager m_RenderManager;

        inline static std::unordered_map<std::string, unsigned int> m_ShaderLookup;

        inline static std::vector<InstanceUpload> m_InstanceUploadQueue;

        inline static unsigned int m_DefaultTextureID = 0;
    };

    using Renderer = Duvet;
}