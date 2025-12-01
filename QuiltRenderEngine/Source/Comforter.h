#pragma once

#include <SparseSet.h>

#include <Transform.h>
#include "GPUBuffer.h"
#include "Mesh.h"
#include "Coverlet.h"

namespace Quilt
{
    enum BatchType
    {
        None,
        Static, 
        Dynamic,
        Instanced
    };

    struct BatchData
    {
        BatchType Type;
        unsigned int VertexLayoutID;
        unsigned int ShaderID;

        bool operator==(const BatchData& other) const
        {
            /*
            TODO: this will later need to be expanded on things that affects the GPU pipeline
            
            this includes:
                texture ID (unless bindless or sprite sheet)
                vertex layout
            */
            return Type == other.Type &&
                /*VertexLayoutID == other.VertexLayoutID &&*/
                ShaderID == other.ShaderID;
        }

        const BatchData& operator=(const BatchData& other)
        {
            ShaderID = other.ShaderID;
            Type = other.Type;

            return *this;
        }
    };

    struct Batch
    {
        BatchData Data;
        GPUBuffer VertexBuffer;
        GPUBuffer IndexBuffer;

        uint64_t VertexCount;
        uint64_t IndexCount;

        std::vector<const Pillow::Transform*> Transforms;
    };

    struct Batches
    {
        std::vector<BatchType> Types;
        std::vector<unsigned int> ShaderHandles;
        std::vector<unsigned int> VertexLayoutHandles;

        std::vector<unsigned int> VertexBufferHandles;
        std::vector<unsigned int> IndexBufferHandles;

        std::vector<uint64_t> VertexCounts;
        std::vector<uint64_t> IndexCounts;

        std::vector<const Pillow::Transform*> Transforms;
    };

    class Comforter
    {
    public:
        //Create a mesh Handle
        unsigned int CreateMesh(BatchData& batchData, const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices, const Pillow::Transform* transform);
        unsigned int RemoveMesh(unsigned int meshID);

        Quilt::Batches& GetBatchStorage() { return m_BatchStorage; }; //TODO: make const later
        unsigned int GetHandle(unsigned int id) { return m_HandleSet.GetData(id); };

        unsigned int NewCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);
        void PopulateBatchBuffer(unsigned int batchHandle, Quilt::BufferType bufferType, const void* data, unsigned int size, unsigned int offset);
        void RemoveTransform(unsigned int batchHandle);
        void RemoveBatch(unsigned int meshHandle);

        void DrawBatches(Quilt::Coverlet& shaderManager, const Pillow::Transform* cameraTransform);

    private:
        unsigned int GetOrCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);

        unsigned int CreateBuffer(BufferType type, unsigned int dataSize, unsigned int dataCount);

        unsigned int CreateHandle(unsigned int BatchHandle);
        void RelocateIndex(unsigned int handle, unsigned int index);

        std::vector<Quilt::Batch> m_Batches;
        Batches m_BatchStorage;
        uint32_t m_BatchCount = 0;

        Quilt::MeshStorage m_Meshes;
        uint32_t m_MeshCount = 0;

        std::vector<unsigned int> m_MeshToHandle;
        std::vector<unsigned int> m_HandleToMesh;

        Frame::SparseSet<unsigned int> m_HandleSet;
        unsigned int m_CurrentHandle = 0;

        GPUBuffers m_GPUBufferStroage;
        uint32_t m_GPUBufferCount = 0;

        std::vector<unsigned int> m_batchHandlesToRemove;
    };

    using Batcher = Comforter;
}