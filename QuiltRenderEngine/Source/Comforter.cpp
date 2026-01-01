#include "Comforter.h"

#include "Vertex.h"
#include "OpenGl/OpenDebugger.h"

unsigned int Quilt::Comforter::CreateMesh(BatchData& batchData, const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices, const Pillow::Transform* transform)
{
    uint32_t newMesh = m_MeshCount;
    m_MeshCount++;

    //Allocate Space for the new meshes
    m_Meshes.BatchIDs.resize(m_MeshCount);
    m_Meshes.LocalIndices.resize(m_MeshCount);
    m_Meshes.VertexOffsets.resize(m_MeshCount);
    m_Meshes.IndexOffsets.resize(m_MeshCount);
    m_Meshes.VertexCounts.resize(m_MeshCount);
    m_Meshes.IndexCounts.resize(m_MeshCount);

    unsigned int batchId = GetOrCreateBatch(16000, 24000, batchData);
    unsigned int vertexOffset = m_BatchStorage.VertexCounts[m_HandleSet.GetData(batchId)];
    unsigned int indexOffset = m_BatchStorage.IndexCounts[m_HandleSet.GetData(batchId)];
    m_BatchStorage.Transforms[batchId] = transform;

    LOG_DEBUG("batch ID: ", batchId);

    //Populate Buffers
    m_BufferManager.PopulateBuffer(m_BatchStorage.VertexBufferHandles[batchId], vertices.data(), vertices.size(), vertexOffset);
    m_BufferManager.PopulateBuffer(m_BatchStorage.IndexBufferHandles[batchId], indices.data(), indices.size(), indexOffset);

    m_Meshes.BatchIDs[newMesh] = batchId;
    m_Meshes.LocalIndices[newMesh] = m_BatchStorage.Transforms.size() - 1; //TODO: Set the transform location
    m_Meshes.VertexOffsets[newMesh] = vertexOffset;
    m_Meshes.IndexOffsets[newMesh] = indexOffset;
    m_Meshes.VertexCounts[newMesh] = vertices.size();
    m_Meshes.IndexCounts[newMesh] = indices.size();

    return newMesh;
}

unsigned int Quilt::Comforter::RemoveMesh(unsigned int meshID)
{
    RemoveBatch(meshID);

    return 0;
}

unsigned int Quilt::Comforter::GetOrCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData)
{
    if(m_BatchCount <= 0)
    {
        return NewCreateBatch(vertexCount, indexCount, batchData);
    }

    for(int i = 0; i < m_BatchCount; i++)
    {
        //TODO: loop through batches and find if a batch has matching batch data
    }

    return NewCreateBatch(vertexCount, indexCount, batchData);
}

unsigned int Quilt::Comforter::NewCreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData)
{
    uint32_t batch = m_BatchCount;
    m_BatchCount++;

    LOG_DEBUG("Creating batch: ", batch);

    m_BatchStorage.Types.resize(m_BatchCount);
    m_BatchStorage.ShaderHandles.resize(m_BatchCount);
    m_BatchStorage.VertexLayoutHandles.resize(m_BatchCount);

    m_BatchStorage.VertexBufferHandles.resize(m_BatchCount);
    m_BatchStorage.IndexBufferHandles.resize(m_BatchCount);

    m_BatchStorage.VertexCounts.resize(m_BatchCount);
    m_BatchStorage.IndexCounts.resize(m_BatchCount);

    m_BatchStorage.Transforms.resize(m_BatchCount);

    LOG_DEBUG("m_BatchCount: ", m_BatchCount);
    LOG_DEBUG("batch id ", batch);
    LOG_DEBUG("batch storage size ", m_BatchStorage.Types.size());

    unsigned int handle = CreateHandle(batch); //Allocates a sparse set for the batch

    LOG_DEBUG("HANDLE after creation ", handle);

    m_BatchStorage.Types[batch] = batchData.Type;
    m_BatchStorage.ShaderHandles[batch] = batchData.ShaderID;

    //Set Up vertex Layout
    GLCall(glGenVertexArrays(1, &m_BatchStorage.VertexLayoutHandles[batch]));
    GLCall(glBindVertexArray(m_BatchStorage.VertexLayoutHandles[batch]));

    //Set up vertex buffer
    m_BatchStorage.VertexBufferHandles[batch] = m_BufferManager.CreateBuffer(Quilt::BufferType::Vertex, sizeof(Quilt::Vertex), vertexCount);

    //Set up index buffer
    m_BatchStorage.IndexBufferHandles[batch] = m_BufferManager.CreateBuffer(Quilt::BufferType::Index, sizeof(unsigned int), indexCount);

    size_t stride = 13 * sizeof(float);

    GLCall(glEnableVertexAttribArray(0)); // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    GLCall(glEnableVertexAttribArray(1)); // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

    GLCall(glEnableVertexAttribArray(2)); // Colour
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

    GLCall(glEnableVertexAttribArray(3)); // Texture Coordinates
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)(10 * sizeof(float)));

    GLCall(glEnableVertexAttribArray(4)); // Texture ID
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, stride, (void*)(12 * sizeof(float)));

    m_BatchStorage.VertexCounts[batch] = 0;
    m_BatchStorage.IndexCounts[batch] = 0;

    return handle;
}

void Quilt::Comforter::PopulateBatchBuffer(unsigned int batchHandle, Quilt::BufferType bufferType, const void* data, unsigned int size, unsigned int offset)
{
    unsigned int bufferHandle;
    unsigned int type;

    switch(bufferType)
    {
        case Quilt::BufferType::Vertex:
            bufferHandle = m_BatchStorage.VertexBufferHandles[batchHandle];
            LOG_DEBUG("Buffer Handle: ", bufferHandle);
            type = GL_ARRAY_BUFFER;
            break;

        case Quilt::BufferType::Index:
            bufferHandle = m_BatchStorage.IndexBufferHandles[batchHandle];
            type = GL_ELEMENT_ARRAY_BUFFER;
            break;
        
        case Quilt::BufferType::Instance:
            LOG_WARN("Instance Buffer not yet implemented");
            break;

        case Quilt::BufferType::Storage:
            LOG_WARN("Storage Buffer not yet implemented");
            break;
    }

    LOG_DEBUG("Buffer Handle to populate: ", bufferHandle);
    LOG_DEBUG("Offset to populate with: ", offset);
    LOG_DEBUG("Data size to populate with: ", size);

    GLCall(glBindBuffer(type, m_GPUBufferStroage.Handles[bufferHandle]));
    GLCall(glBufferSubData(type, offset * m_GPUBufferStroage.DataSizes[bufferHandle], size * m_GPUBufferStroage.DataSizes[bufferHandle], data));

    LOG_DEBUG("FINISHED POPULATING BUFFER: ", bufferHandle);
}

void Quilt::Comforter::RemoveBatch(unsigned int meshHandle)
{
    unsigned int handle = m_Meshes.BatchIDs[meshHandle];

    uint32_t last = m_BatchCount - 1;

    LOG_DEBUG("Last handle: ", last);

    //Swap the index with the last in array
    std::swap(m_BatchStorage.Types[handle], m_BatchStorage.Types[last]);
    std::swap(m_BatchStorage.ShaderHandles[handle], m_BatchStorage.ShaderHandles[last]);
    std::swap(m_BatchStorage.VertexLayoutHandles[handle], m_BatchStorage.VertexLayoutHandles[last]);

    std::swap(m_BatchStorage.VertexBufferHandles[handle], m_BatchStorage.VertexBufferHandles[last]);
    std::swap(m_BatchStorage.IndexBufferHandles[handle], m_BatchStorage.IndexBufferHandles[last]);

    std::swap(m_BatchStorage.VertexCounts[handle], m_BatchStorage.VertexCounts[last]);
    std::swap(m_BatchStorage.IndexCounts[handle], m_BatchStorage.IndexCounts[last]);

    std::swap(m_BatchStorage.Transforms[handle], m_BatchStorage.Transforms[last]);

    LOG_DEBUG("Swaping: ", handle, " and ", last);

    //RelocateIndex(m_IndexToHandle[], index);
    m_HandleSet.Swap(handle, last);
    m_batchHandlesToRemove.push_back(handle);

    //TODO: Swap to deffered updates

    //Remove the last index
    m_BatchStorage.Types.pop_back();
    m_BatchStorage.ShaderHandles.pop_back();
    m_BatchStorage.VertexLayoutHandles.pop_back();

    m_BatchStorage.VertexBufferHandles.pop_back();
    m_BatchStorage.IndexBufferHandles.pop_back();

    m_BatchStorage.VertexCounts.pop_back();
    m_BatchStorage.IndexCounts.pop_back();

    m_BatchStorage.Transforms.pop_back();

    m_BatchCount--;

    //return last;
}

void Quilt::Comforter::DrawBatches(Quilt::Coverlet& shaderManager, const Pillow::Transform* cameraTransform, float xSizePercent, float ySizePercent)
{
    for(unsigned int handle : m_HandleSet.GetAllData())
    {
        //bind shader from batch
        if(!glIsProgram(m_BatchStorage.ShaderHandles[handle]))
        {
            LOG_WARN("Batch does not have a shader Bound");
            continue;
        }

        GLCall(glUseProgram(m_BatchStorage.ShaderHandles[handle]));

        float aspect = xSizePercent / ySizePercent;
        float zoom = 5.0f;

        float left = -zoom * aspect;
        float right = zoom * aspect;
        float bottom = -zoom;
        float top = zoom;

        glm::mat4 proj = glm::orthoLH(left, right, bottom, top, -1.0f, 500.0f); // camera

        glm::vec3 camPos = glm::vec3(cameraTransform->Position.x, cameraTransform->Position.y, cameraTransform->Position.z);
        glm::vec3 targetPos = camPos + glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 view = glm::lookAtLH(camPos, targetPos, upVec);

        switch(m_BatchStorage.Types[handle])
        {
            case Quilt::BatchType::None:
                break;
            
            case Quilt::BatchType::Static:
                break;
            
            case Quilt::BatchType::Dynamic:
                glm::mat4 model;
                for (const Pillow::Transform* transform : m_BatchStorage.Transforms)
                {
                    model = glm::translate(glm::mat4(1.0f), glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z)) *
                            glm::yawPitchRoll(
                                glm::radians(transform->Rotation.y),
                                glm::radians(transform->Rotation.x),
                                glm::radians(transform->Rotation.z)
                            ) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(transform->Scale.x, transform->Scale.y, transform->Scale.z));

                    shaderManager.SetUniformMat4f(m_BatchStorage.ShaderHandles[handle], "u_Model", model);
                    shaderManager.SetUniformMat4f(m_BatchStorage.ShaderHandles[handle], "u_View", view);
                    shaderManager.SetUniformMat4f(m_BatchStorage.ShaderHandles[handle], "u_Projection", proj);

                    int samplers[32];
                    for(int i = 0; i < 32; ++i)
                    {
                        samplers[i] = i;
                    } 

                    shaderManager.SetUniform1iv(m_BatchStorage.ShaderHandles[handle], "u_Textures", 32, samplers);

                    //for(const Quilt::Texture& texture : m_TextureManager.GetTextures())
                    //{
                    //    GLCall(glActiveTexture(GL_TEXTURE0 + texture.Slot));
                    //    GLCall(glBindTexture(GL_TEXTURE_2D, texture.Handle));
                    //}

                    GLCall(glBindVertexArray(m_BatchStorage.VertexLayoutHandles[handle]));
                    m_BufferManager.BindBuffer(m_BatchStorage.VertexBufferHandles[handle]);
                    m_BufferManager.BindBuffer(m_BatchStorage.IndexBufferHandles[handle]);

                    //TODO: This draw seems tedious ideally this would be non-trivial -> m_BufferManager.GetBufferStorage().DataCounts[m_BatchStorage.IndexBufferHandles[handle]]
                    GLCall(glDrawElements(GL_TRIANGLES, m_BufferManager.GetBufferStorage().DataCounts[m_BatchStorage.IndexBufferHandles[handle]], GL_UNSIGNED_INT, nullptr));
                }
                break;

            case Quilt::BatchType::Instanced:
                break;
        }
    }

    for(unsigned int batchHandle : m_batchHandlesToRemove)
    {
       m_HandleSet.Remove(batchHandle);
    }
}

unsigned int Quilt::Comforter::CreateHandle(unsigned int BatchHandle)
{
    unsigned int createdHandle = m_CurrentHandle;

    LOG_DEBUG("Creating handle: ", createdHandle, " with batch handle ", BatchHandle);

    m_HandleSet.Insert(m_CurrentHandle, BatchHandle);
    m_CurrentHandle++;

    return createdHandle;
}

void Quilt::Comforter::RelocateIndex(unsigned int handle, unsigned int index)
{
    
}