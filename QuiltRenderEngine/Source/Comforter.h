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
        uint64_t VertexBufferHandle;
        uint64_t IndexBufferHandle;

        uint64_t VertexCount;
        uint64_t IndexCount;

        std::vector<const Pillow::Transform*> Transforms;
    };

    /*TODO: SoA better for processing a single field over many objects where AoS is better for objects using many fields!
        - Batches are itterated per batch touching all feilds at a time.
        - Cameras are itterated per camera touching all feilds at a time.

        - Meshes are itterated per item touching one feild at a time, i.e. batchID.
        - GPUBuffers are sent over to the GPU giving back a ID meaning we only ever use the ID after submission!
    */

    class Comforter
    {
    public:
        /*
            Creates a batch handle to return back to the Mesh SoA. 
        */
        unsigned int GetOrCreateBatch(unsigned int vertexBufferHandle, unsigned int indexBufferHandle, BatchData& batchData);
        void RemoveBatch(unsigned int batchHandle) { m_RemovedBatchIDs.push_back(batchHandle); return m_BatchStorage.Remove(batchHandle); };
        bool IsBatchEmpty(unsigned int batchHandle) { return true; };

        const std::vector<Quilt::Batch>& GetAllBatches() { return m_BatchStorage.GetAllData(); };

        const Quilt::Batch GetBatch(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle); };
        const BatchData GetBatchData(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).Data; };
        const uint64_t GetVertexBufferHandle(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).VertexBufferHandle; };
        const uint64_t GetIndexBufferHandle(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).IndexBufferHandle; };
        const uint64_t GetVertexCount(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).VertexCount; };
        const uint64_t GetIndexCount(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).IndexCount; };

        const Pillow::Transform* GetTransform(unsigned int batchHandle, uint64_t indexOffset);

        unsigned int AddTransform(unsigned int batchHandle, const Pillow::Transform* transform);

    private:
        unsigned int CreateBatchHandle(unsigned int vertexBufferHandle, unsigned int indexBufferHandle, BatchData& batchData);
        unsigned int GetBatchHandle(unsigned int vertexBufferHandle, unsigned int indexBufferHandle, BatchData& batchData);

        unsigned int m_BatchHandleCount = 0;
        std::vector<unsigned int> m_RemovedBatchIDs;
        Frame::SparseSet<Quilt::Batch> m_BatchStorage;
    };

    using BatchManager = Comforter;
}