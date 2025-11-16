#include "Comforter.h"

#include "Vertex.h"
#include "OpenGl/OpenDebugger.h"

//TODO: clean this function up
Quilt::Batch& Quilt::Comforter::GetOrCreateBatch(BatchData& batchData)
{
    if(m_Batches.empty())
    {
        return m_Batches.emplace_back(CreateBatch(16000, 24000, batchData));
    }

    for(Quilt::Batch& batch : m_Batches)
    {
        //Get batch
        if(batch.Data == batchData)
        {
            return batch;
        }
    }

    return m_Batches.emplace_back(CreateBatch(16000, 24000, batchData));
}

Quilt::Batch Quilt::Comforter::CreateBatch(unsigned int vertexCount, unsigned int indexCount, BatchData& batchData)
{
    Quilt::Batch newBatch;
    newBatch.Data = batchData;

    //Set Up vertex Layout
    GLCall(glGenVertexArrays(1, &newBatch.Data.VertexLayoutID));
    GLCall(glBindVertexArray(newBatch.Data.VertexLayoutID));

    //Set Up vertex buffer
    newBatch.VertexBuffer.Type = Quilt::BufferType::Vertex;
    newBatch.VertexBuffer.DataSize = sizeof(Quilt::Vertex);
    newBatch.VertexBuffer.DataCount = vertexCount;

    GLCall(glGenBuffers(1, &newBatch.VertexBuffer.Handle)); // Generates Buffer and assigns it to m_RendererID
    GLCall(glBindBuffer(GL_ARRAY_BUFFER /*VertexBuffer.Type*/, newBatch.VertexBuffer.Handle));
    GLCall(glBufferData(GL_ARRAY_BUFFER, newBatch.VertexBuffer.DataSize * newBatch.VertexBuffer.DataCount, nullptr, GL_DYNAMIC_DRAW));

    //Set Up index buffer
    newBatch.IndexBuffer.Type = Quilt::BufferType::Index;
    newBatch.IndexBuffer.DataSize = sizeof(unsigned int);
    newBatch.IndexBuffer.DataCount = indexCount;

    GLCall(glGenBuffers(1, &newBatch.IndexBuffer.Handle)); // Generates Buffer and assigns it to m_RendererID
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER/*IndexBuffer.Type*/, newBatch.IndexBuffer.Handle));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, newBatch.IndexBuffer.DataSize * newBatch.IndexBuffer.DataCount, nullptr, GL_DYNAMIC_DRAW));

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

    newBatch.IndexCount = 0;
    newBatch.VertexCount = 0;

    return newBatch;
}