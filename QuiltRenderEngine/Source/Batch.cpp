#include "Batch.h"

#include "Vertex.h"
#include "OpenGl/OpenDebugger.h"

unsigned int Quilt::Comforter::CreateBatchHandle(unsigned int vertexBufferHandle, unsigned int indexBufferHandle, unsigned int vertexArrayHandle, BatchData& batchData)
{
    unsigned int batchHandle;

    if(m_RemovedBatchIDs.empty())
    {
        batchHandle = m_BatchHandleCount;
        m_BatchHandleCount++;

        LOG_INFO("Created Batch ID: ", batchHandle);
    }
    else
    {
        batchHandle = m_RemovedBatchIDs.back();
        m_RemovedBatchIDs.pop_back();

        LOG_INFO("Recycled Batch: ", batchHandle);
    }

    Quilt::Batch newBatch;
    newBatch.Data = batchData;
    newBatch.VertexBufferHandle = vertexBufferHandle;
    newBatch.IndexBufferHandle = indexBufferHandle;
    newBatch.VertexArrayHandle = vertexArrayHandle;

    m_BatchStorage.Insert(batchHandle, newBatch);

    //check if batch data already exists and add the new batch
    if(FindBatchsWithData(batchData))
    {
        m_BatchDataLookUp.at(batchData).push_back(batchHandle);
    }
    else
    {
        std::vector<unsigned int> handles;
        handles.push_back(batchHandle);
        m_BatchDataLookUp.emplace(batchData, handles);
    }

    return batchHandle;
}

void Quilt::Comforter::RemoveBatch(unsigned int batchHandle)
{
    LOG_INFO("Removed Batch: ", batchHandle);
    BatchData data = GetBatch(batchHandle).Data;
    std::vector<unsigned int>& handles = m_BatchDataLookUp.at(data);
    handles.erase(std::remove(handles.begin(), handles.end(), batchHandle), handles.end());

    if(handles.empty())
    {
        m_BatchDataLookUp.erase(data);
    }

    m_RemovedBatchIDs.push_back(batchHandle);
    m_BatchStorage.Remove(batchHandle);
}

unsigned int Quilt::Comforter::GetBatchHandle(BatchData& batchData)
{
    unsigned int handle;

    for(unsigned int batchHandle : GetBatchesWithData(batchData))
    {
        handle = batchHandle;
        break;
    }

    return handle;
}

bool Quilt::Comforter::FindBatchsWithData(BatchData& batchData)
{
    return m_BatchDataLookUp.find(batchData) != m_BatchDataLookUp.end();
}

std::vector<unsigned int>& Quilt::Comforter::GetBatchesWithData(BatchData& batchData)
{
    return m_BatchDataLookUp.at(batchData);
}

void Quilt::Comforter::UpdateTransform(unsigned int batchHandle, uint64_t drawInfoOffset, Pillow::Transform& transform)
{
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform.Position.x, transform.Position.y, transform.Position.z)) *
                            glm::yawPitchRoll(
                                glm::radians(transform.Rotation.y),
                                glm::radians(transform.Rotation.x),
                                glm::radians(transform.Rotation.z)
                            ) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(transform.Scale.x, transform.Scale.y, transform.Scale.z));


    m_BatchStorage.GetData(batchHandle).DrawInfos[drawInfoOffset].TransformMatrix = matrix;
}

unsigned int Quilt::Comforter::AddDrawInfo(unsigned int batchHandle, Quilt::DrawInfo drawInfo)
{
    m_BatchStorage.GetData(batchHandle).DrawInfos.push_back(drawInfo);

    return m_BatchStorage.GetData(batchHandle).DrawInfos.size() - 1;
}