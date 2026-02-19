#include "Comforter.h"

#include "Vertex.h"
#include "OpenGl/OpenDebugger.h"


unsigned int Quilt::Comforter::GetOrCreateBatch(unsigned int vertexBufferHandle, unsigned int indexBufferHandle, BatchData& batchData)
{
    /*if (m_BatchStorage.empty())
    {
        return CreateBatchHandle(batchData);
    }*/

    //TODO: Decide when to get/create a new batch
    return CreateBatchHandle(vertexBufferHandle, indexBufferHandle, batchData);
}

unsigned int Quilt::Comforter::CreateBatchHandle(unsigned int vertexBufferHandle, unsigned int indexBufferHandle, BatchData& batchData)
{
    unsigned int newBatchHandle;

    if(m_RemovedBatchIDs.empty())
    {
        newBatchHandle = m_BatchHandleCount;
        m_BatchHandleCount++;
    }
    else
    {
        newBatchHandle = m_RemovedBatchIDs.back();
        m_RemovedBatchIDs.pop_back();
    }

    Quilt::Batch newBatch;
    newBatch.Data = batchData;
    newBatch.VertexBufferHandle = vertexBufferHandle;
    newBatch.IndexBufferHandle = indexBufferHandle;

    newBatch.VertexCount = 0;
    newBatch.IndexCount = 0;

    //TODO: remove this out of here
    //Generate vertex array
    GLCall(glGenVertexArrays(1, &newBatch.Data.VertexLayoutID));
    GLCall(glBindVertexArray(newBatch.Data.VertexLayoutID));

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

    m_BatchStorage.Insert(newBatchHandle, newBatch);

    return newBatchHandle;
}

unsigned int Quilt::Comforter::GetBatchHandle(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData)
{
    return 0;
}

unsigned int Quilt::Comforter::AddTransform(unsigned int batchHandle, const Pillow::Transform* transform)
{
    //TODO: this needs to be more advanced as users may need to add and remove transforms
    m_BatchStorage.GetData(batchHandle).Transforms.push_back(transform);

    LOG_INFO("Transforms size ", m_BatchStorage.GetData(batchHandle).Transforms.size());

    return m_BatchStorage.GetData(batchHandle).Transforms.size() - 1;
}