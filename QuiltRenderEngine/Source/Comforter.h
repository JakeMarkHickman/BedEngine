#pragma once

#include <SparseSet.h>

#include <Transform.h>
#include "GPUBuffer.h"
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
        std::vector<Quilt::Batch>& GetBatches() { return m_Batches; };

        Quilt::Batches& GetBatchStorage() { return m_BatchStorage; }; //TODO: make const later
        unsigned int GetHandle(unsigned int id) { return m_HandleSet.GetData(id); };

        Quilt::Batch& GetOrCreateBatch(BatchData& batchData);
        [[deprecated("Replaced by NewCreateBatch, which will become the standard with SoA.")]]
        Quilt::Batch CreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);

        unsigned int NewCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData, const Pillow::Transform* transform);
        void PopulateBatchBuffer(unsigned int batchHandle, Quilt::BufferType bufferType, const void* data, unsigned int size, unsigned int offset);
        void RemoveTransform(unsigned int batchHandle);
        void RemoveBatch(unsigned int batchHandle);

        void DrawBatches(Quilt::Coverlet& shaderManager, const Pillow::Transform* cameraTransform);

    private:
        unsigned int CreateBuffer(BufferType type, unsigned int dataSize, unsigned int dataCount);

        unsigned int CreateHandle(unsigned int BatchHandle);
        void RelocateIndex(unsigned int handle, unsigned int index);

        std::vector<Quilt::Batch> m_Batches;
        Batches m_BatchStorage;
        uint32_t m_BatchCount = 0;

        Frame::SparseSet<unsigned int> m_HandleSet;
        unsigned int m_CurrentHandle = 0;

        GPUBuffers m_GPUBufferStroage;
        uint32_t m_GPUBufferCount = 0;
    };

    using Batcher = Comforter;
}