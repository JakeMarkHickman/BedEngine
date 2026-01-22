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
        unsigned int GetOrCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);


        const BatchData& GetBatchData(unsigned int batchHandle);
        const GPUBuffer& GetVertexBuffer(unsigned int batchHandle);
        const GPUBuffer& GetIndexBuffer(unsigned int batchHandle);
        const uint64_t& GetVertexCount(unsigned int batchHandle);
        const uint64_t& GetIndexCount(unsigned int batchHandle);


        const Pillow::Transform* GetTransform(unsigned int batchHandle, uint64_t indexOffset);

    private:
        unsigned int CreateBatchHandle(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);
        unsigned int GetBatchHandle(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);

        unsigned int m_BatchHandleCount = 0;
        Frame::SparseSet<Quilt::Batch> m_BatchStorage;
    }

    /*class Comforter
    {
    public:
        //Create a mesh Handle
        unsigned int CreateMesh(BatchData& batchData, const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices, const Pillow::Transform* transform);
        unsigned int RemoveMesh(unsigned int meshID);

        unsigned int GetOrCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);

        Quilt::Batches& GetBatchStorage() { return m_BatchStorage; }; //TODO: make const later
        unsigned int GetHandle(unsigned int id) { return m_HandleSet.GetData(id); };

        unsigned int NewCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData);
        void RemoveTransform(unsigned int batchHandle);
        void RemoveBatch(unsigned int meshHandle);

        void DrawBatches(Quilt::Coverlet& shaderManager, const Pillow::Transform* cameraTransform, float xSizePercent, float ySizePercent);

    private:

        unsigned int CreateHandle(unsigned int BatchHandle);
        void RelocateIndex(unsigned int handle, unsigned int index);

        BufferManager m_BufferManager;

        Batches m_BatchStorage;
        uint32_t m_BatchCount = 0;

        std::vector<unsigned int> m_MeshToHandle;
        std::vector<unsigned int> m_HandleToMesh;

        Frame::SparseSet<unsigned int> m_HandleSet;
        unsigned int m_CurrentHandle = 0;

        std::vector<unsigned int> m_batchHandlesToRemove;
    };*/

    using BatchManager = Comforter;
}