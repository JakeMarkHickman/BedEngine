#pragma once

#include <SparseSet.h>

#include <Transform.h>
#include "GPUBuffer.h"
#include "Mesh.h"

namespace Quilt
{
    //TODO: information that is used on how to draw something is used in here
    struct DrawInfo
    {
        glm::mat4 TransformMatrix;
        const Pillow::Transform* Transform;
        unsigned int IndexCount;
        unsigned int IndexOffset;

        const DrawInfo& operator=(const DrawInfo& other)
        {
            TransformMatrix = other.TransformMatrix;
            IndexCount = other.IndexCount;
            IndexOffset = other.IndexOffset;

            return *this;
        }
    };

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
        unsigned int ShaderID;
        unsigned int TextureID;

        bool operator==(const BatchData& other) const
        {
            /*
            TODO: this will later need to be expanded on things that affects the GPU pipeline
            
            this includes:
                texture ID (unless bindless or sprite sheet)
                vertex layout
            */
            return Type == other.Type &&
                ShaderID == other.ShaderID &&
                TextureID == other.TextureID;
        }

        bool operator!=(const BatchData& other) const
        {
            /*
            TODO: this will later need to be expanded on things that affects the GPU pipeline
            
            this includes:
                texture ID (unless bindless or sprite sheet)
                vertex layout
            */
            return Type != other.Type &&
                ShaderID != other.ShaderID &&
                TextureID != other.TextureID;
        }

        const BatchData& operator=(const BatchData& other)
        {
            ShaderID = other.ShaderID;
            Type = other.Type;
            TextureID = other.TextureID;

            return *this;
        }
    };

    struct Batch
    {
        BatchData Data;
        uint64_t VertexBufferHandle;
        uint64_t IndexBufferHandle;

        unsigned int VertexLayoutID;

        std::vector<DrawInfo> DrawInfos;
    };
}

namespace std
{
    template<>
    struct hash<Quilt::BatchData>
    {
        size_t operator()(const Quilt::BatchData& data) const noexcept
        {
            size_t type = std::hash<int>{}(static_cast<int>(data.Type));
            size_t shaderID = std::hash<unsigned int>{}(data.ShaderID);
            size_t textureID = std::hash<unsigned int>{}(data.TextureID);

            return type ^ (shaderID << 1) ^ (textureID << 2);
        }
    };
}

namespace Quilt
{
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
        unsigned int CreateBatchHandle(unsigned int vertexBufferHandle, unsigned int indexBufferHandle, BatchData& batchData);
        void RemoveBatch(unsigned int batchHandle);
        bool IsBatchEmpty(unsigned int batchHandle) { return true; };

        bool FindBatchsWithData(BatchData& batchData);
        std::vector<unsigned int>& GetBatchesWithData(BatchData& batchData);

        const std::vector<Quilt::Batch>& GetAllBatches() { return m_BatchStorage.GetAllData(); };

        Quilt::Batch& GetBatch(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle); };
        const BatchData GetBatchData(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).Data; };
        const uint64_t GetVertexBufferHandle(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).VertexBufferHandle; };
        const uint64_t GetIndexBufferHandle(unsigned int batchHandle) { return m_BatchStorage.GetData(batchHandle).IndexBufferHandle; };
        const Pillow::Transform* GetTransform(unsigned int batchHandle, uint64_t indexOffset);

        void UpdateTransform(unsigned int batchHandle, uint64_t drawInfoOffset, Pillow::Transform& transform);

        unsigned int AddDrawInfo(unsigned int batchHandle, Quilt::DrawInfo DrawInfo);

    private:
        unsigned int GetBatchHandle(BatchData& batchData);

        unsigned int m_BatchHandleCount = 0;
        std::vector<unsigned int> m_RemovedBatchIDs;
        Frame::SparseSet<Quilt::Batch> m_BatchStorage;

        std::unordered_map<BatchData, std::vector<unsigned int>> m_BatchDataLookUp;
    };

    using BatchManager = Comforter;
}