#pragma once

#include <Transform.h>
#include "GPUBuffer.h"

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

    class Comforter
    {
    public:
        std::vector<Quilt::Batch>& GetBatches() { return m_Batches; };

        Quilt::Batch& GetOrCreateBatch(BatchData& batchData);
        Quilt::Batch CreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);

    private:
        std::vector<Quilt::Batch> m_Batches;
    };

    using Batcher = Comforter;
}