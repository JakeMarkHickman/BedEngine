#include "Duvet.h"

#include <algorithm>

/*
    TODO: THIS WHOLE THING NEEDS A REWORK TO GET WORKING PROPERLY

    Mesh should just be the information of a mesh. When created
    the mesh should return a handle to a mesh that is stored in
    memory. This allows for quick access if the mesh is common
    like a sprite.
        - Vertices
        - Indices
    
    The external entity in Bed Engines case will hold all information
    about the state of the component. It stores the Texture ID, Mesh ID,
    Material ID ect. The engine will be the single source of truth. This
    means this can be simplified as state is external, expansion for later
    would be Quilt managing the life cycle for OOP or other achitectures.
*/

//TODO: This will be outside the lib in Quilts SDK
void Quilt::Duvet::Init()
{
    LOG_INFO("Texture slots available on GPU: ", m_TextureManager.GetTextureSlots());

    LOG_INFO("Vector 2 size: ", sizeof(Pillow::Vector2f(0.0f)));
    LOG_INFO("SpriteInstanceData size: ", sizeof(Quilt::SpriteInstanceData));
}

unsigned int Quilt::Duvet::CreateShader(std::string shaderName, std::string vertexShader, std::string fragmentShader)
{
    unsigned int shaderHandle;

    if(m_ShaderLookup.find(shaderName) != m_ShaderLookup.end())
    {
        LOG_FATAL("Shader already exists with name: ", shaderName);
        return 0;
    }

    if(m_ShaderManager.IsShaderProgram(vertexShader, fragmentShader))
    {
        LOG_ERROR("Shader Program already Exists");
        shaderHandle = m_ShaderManager.GetShaderProgram(vertexShader, fragmentShader);
    }
    else
    {
        shaderHandle = m_ShaderManager.AddShader(vertexShader, fragmentShader);
    }
    
    m_ShaderLookup.emplace(shaderName, shaderHandle);
    return shaderHandle;
}

unsigned int Quilt::Duvet::GetShader(std::string shaderName)
{
    if(m_ShaderLookup.find(shaderName) == m_ShaderLookup.end())
    {
        LOG_FATAL("No Shader Assigned with name: ", shaderName);
        return 0;
    }

    return m_ShaderLookup.at(shaderName);
}

void Quilt::Duvet::SetDefaultTexture(const std::string& path)
{
    m_DefaultTextureID = m_TextureManager.AddTexture(path, Quilt::TextureFiltering::Nearest);
}

unsigned int Quilt::Duvet::GetDefaultTexture()
{
    if(!m_TextureManager.IsTexture(m_DefaultTextureID))
    {
        LOG_FATAL("Default Texture exceeds assigned textures: ", m_DefaultTextureID);
    }

    return m_DefaultTextureID;
};

unsigned int Quilt::Duvet::CreateMesh(const std::string& name, const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int handle;
    if(m_MeshManager.IsMeshCached(name))
    {
        handle = m_MeshManager.GetMeshHandle(name);
    }
    else
    {
        Quilt::Mesh mesh;

        mesh.Vertices = vertices;
        mesh.Indices = indices;
        handle = m_MeshManager.CreateMeshHandle(name, mesh);
    }

    return handle;
}

unsigned int Quilt::Duvet::CreateMesh(const std::string& path)
{
    unsigned int handle;
    if(m_MeshManager.IsMeshCached(path))
    {
        handle = m_MeshManager.GetMeshHandle(path);
    }
    else
    {
        handle = m_MeshManager.CreateMeshHandle(path);
    }

    return handle;
}

void Quilt::Duvet::CreateRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID)
{
    //CreateDynamicRenderableObject(entityID, meshID, shaderID);
    CreateInstancedRenderableObject(entityID, meshID, shaderID);
}

void Quilt::Duvet::CreateDynamicRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID)
{
    unsigned int batchHandle;

    Quilt::VertexBufferLayout twoDimentionLayout;
        twoDimentionLayout.Push<float>(3);
        twoDimentionLayout.Push<float>(3);
        twoDimentionLayout.Push<float>(4);
        twoDimentionLayout.Push<float>(2);
        twoDimentionLayout.Push<float>(1);

    Quilt::Mesh& mesh = m_MeshManager.GetMeshData(meshID);
    Quilt::BatchData data;
    data.VertexLayout = twoDimentionLayout;
    data.ShaderID = shaderID;
    data.TextureID = GetDefaultTexture();
    data.Type = Quilt::BatchType::Dynamic;
    
    if(m_BatchManager.FindBatchsWithData(data))
    {
        for(unsigned int& handle : m_BatchManager.GetBatchesWithData(data))
        {
            batchHandle = handle;
            break;
        }
    }
    else
    {
        LOG_INFO("No batches with data");

        //Create the buffers
        unsigned int vertexCount = 16000;
        unsigned int indexCount = 24000;
        unsigned int vertexBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Vertex, sizeof(Quilt::Vertex), vertexCount);
        unsigned int indexBufferHandle;
        unsigned int vertArray;

        if(!m_VertexArrayManager.IsVertexArray(twoDimentionLayout))
        {
            LOG_INFO("Creating VAO");
            vertArray = m_VertexArrayManager.CreateVertexArray(twoDimentionLayout);
        }
        else
        {
            LOG_INFO("Getting VAO");
            vertArray = m_VertexArrayManager.GetVertexArray(twoDimentionLayout);
        }

        indexBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Index, sizeof(unsigned int), indexCount);

        batchHandle = m_BatchManager.CreateBatchHandle(vertexBufferHandle, indexBufferHandle, vertArray, data);
    }

    unsigned int vertexBufferHandle = m_BatchManager.GetVertexBufferHandle(batchHandle);
    unsigned int indexBufferHandle = m_BatchManager.GetIndexBufferHandle(batchHandle);

    //Create the batch and assign data
    DrawInfo info;
    info.IndexCount = mesh.Indices.size();
    info.IndexOffset = m_BufferManager.GetOccupiedCount(indexBufferHandle);

    unsigned int drawInfoOffset = m_BatchManager.AddDrawInfo(batchHandle, info);

    Quilt::RenderableObject object;
    object.BatchID = batchHandle;
    object.DrawInfoOffset = drawInfoOffset;
    object.VertexOffset = m_BufferManager.GetOccupiedCount(vertexBufferHandle);
    object.VertexCount = mesh.Vertices.size();
    object.MeshHandle = meshID;

    std::vector<unsigned int> offsetIndices = mesh.Indices;
    for(unsigned int& index : offsetIndices)
    {
        index += object.VertexOffset;
    }

    //Populate buffers
    m_BufferManager.PopulateBuffer(vertexBufferHandle, mesh.Vertices.data(), mesh.Vertices.size());
    m_BufferManager.PopulateBuffer(indexBufferHandle, offsetIndices.data(), offsetIndices.size());

    m_RenderManager.CreateRenderableObject(entityID, object);
}

void Quilt::Duvet::CreateInstancedRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID)
{
    unsigned int batchHandle;

    Quilt::VertexBufferLayout twoDimentionLayout;
        twoDimentionLayout.Push<float>(3);
        twoDimentionLayout.Push<float>(3);
        twoDimentionLayout.Push<float>(4);
        twoDimentionLayout.Push<float>(2);
        twoDimentionLayout.Push<float>(1);

    Quilt::Mesh& mesh = m_MeshManager.GetMeshData(meshID);
    Quilt::BatchData data;
    data.VertexLayout = twoDimentionLayout;
    data.ShaderID = shaderID;
    data.TextureID = GetDefaultTexture();
    data.Type = Quilt::BatchType::Instanced;

    bool foundBatch = false;
    if(m_BatchManager.FindBatchsWithData(data))
    {
        for(unsigned int& handle : m_BatchManager.GetBatchesWithData(data))
        {
            if(m_BatchManager.GetBatch(handle).MeshID == meshID)
            {
                foundBatch = true;
                batchHandle = handle;
                break;
            }
        }
    }

    if(!foundBatch)
    {
        LOG_INFO("No batch found... creating");

        //Size for this mesh
        unsigned int vertexCount = mesh.Vertices.size();
        unsigned int indexCount = mesh.Indices.size();

        unsigned int vertexBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Vertex, sizeof(Quilt::Vertex), vertexCount);

        unsigned int vertArray;
        if(!m_VertexArrayManager.IsVertexArray(twoDimentionLayout))
        {
            LOG_INFO("Creating VAO");
            vertArray = m_VertexArrayManager.CreateVertexArray(twoDimentionLayout);
        }
        else
        {
            LOG_INFO("Getting VAO");
            vertArray = m_VertexArrayManager.GetVertexArray(twoDimentionLayout);
        }
        
        unsigned int indexBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Index, sizeof(unsigned int), indexCount);

        unsigned int maxInstances = 25000;
        unsigned int instanceBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Storage, sizeof(Quilt::SpriteInstanceData), maxInstances, 0);

        batchHandle = m_BatchManager.CreateBatchHandle(vertexBufferHandle, indexBufferHandle, vertArray, data, instanceBufferHandle, meshID, 0);

        m_BufferManager.PopulateBuffer(vertexBufferHandle, mesh.Vertices.data(), mesh.Vertices.size());
        m_BufferManager.PopulateBuffer(indexBufferHandle, mesh.Indices.data(), mesh.Indices.size());
    } 

    //TODO: not actually populating SpriteInstanceData yet

    unsigned int indexBufferHandle = m_BatchManager.GetIndexBufferHandle(batchHandle);

    DrawInfo info;
    info.IndexCount = mesh.Indices.size();
    info.IndexOffset = m_BufferManager.GetOccupiedCount(indexBufferHandle);

    unsigned int drawInfoOffset = m_BatchManager.AddDrawInfo(batchHandle, info);

    Quilt::Batch& batch = m_BatchManager.GetBatch(batchHandle);
    unsigned int instanceSlot = batch.InstanceCount;
    batch.InstanceCount++;

    Quilt::RenderableObject object;
    object.BatchID = batchHandle;
    object.InstanceSlot = instanceSlot;
    object.MeshHandle = meshID;
    object.VertexCount = 0;
    object.DrawInfoOffset = 0;
    object.VertexOffset = 0;

    m_RenderManager.CreateRenderableObject(entityID, object);
}

void Quilt::Duvet::UpdateSpriteInstanceData(uint64_t entityID, Pillow::Transform& transform, Pillow::Vector4f& colour, Pillow::Vector2f& textureCoords, float& textureID)
{
    Quilt::RenderableObject& object = m_RenderManager.GetRenderableObject(entityID);
    Quilt::Batch& batch = m_BatchManager.GetBatch(object.BatchID);

    Quilt::SpriteInstanceData data;
    data.TransfomMatrix = transform.GetMatrix();
    data.Colour = colour;
    data.TextureCoordinates = textureCoords;
    data.TextureID = textureID;

    unsigned int buffer = m_BufferManager.GetBufferStorage().Handles[batch.InstanceBufferHandle];

    m_BufferManager.PopulateBuffer(batch.InstanceBufferHandle, &data, 1, object.InstanceSlot);

    GLCall(glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT));
}

void Quilt::Duvet::UpdateTransform(uint64_t entityID, Pillow::Transform& transform)
{
    Quilt::RenderableObject& object = m_RenderManager.GetRenderableObject(entityID);
    Quilt::BatchType type = m_BatchManager.GetBatch(object.BatchID).Data.Type;

    switch (type)
    {
    case Quilt::BatchType::Dynamic:
            m_BatchManager.UpdateTransform(object.BatchID, object.DrawInfoOffset, transform);
        break;
    
    case Quilt::BatchType::Instanced:
            LOG_DEBUG("Update instance transform here");
        break;

    default:
        break;
    }
}

void Quilt::Duvet::RemoveRenderableObject(uint64_t entityID)
{
    Quilt::RenderableObject& object = m_RenderManager.GetRenderableObject(entityID);
    unsigned int lastEntity = m_RenderManager.GetLastRenderableEntity();

    unsigned int removedBatchID = object.BatchID;
    unsigned int removedVertexCount = object.VertexCount;
    unsigned int removedIndexCount = m_BatchManager.GetDrawInfo(removedBatchID, object.DrawInfoOffset).IndexCount;

    if(lastEntity != entityID)
    {
        Quilt::RenderableObject& lastObject = m_RenderManager.GetRenderableObject(lastEntity);
        unsigned int lastVertHandle = m_BatchManager.GetVertexBufferHandle(lastObject.BatchID);
        unsigned int lastIndexHandle = m_BatchManager.GetIndexBufferHandle(lastObject.BatchID);

        unsigned int vertHandle = m_BatchManager.GetVertexBufferHandle(object.BatchID);
        unsigned int indexHandle = m_BatchManager.GetIndexBufferHandle(object.BatchID);

        CopyInfo vertCopy;
        vertCopy.ReadBuffer = lastVertHandle;
        vertCopy.WriteBuffer = vertHandle;
        vertCopy.ReadOffset = lastObject.VertexOffset;
        vertCopy.WriteOffset = object.VertexOffset;
        vertCopy.Count = lastObject.VertexCount;

        CopyInfo indexCopy;
        indexCopy.ReadBuffer = lastIndexHandle;
        indexCopy.WriteBuffer = indexHandle;
        indexCopy.ReadOffset = m_BatchManager.GetDrawInfo(lastObject.BatchID, lastObject.DrawInfoOffset).IndexOffset;
        indexCopy.WriteOffset = m_BatchManager.GetDrawInfo(object.BatchID, object.DrawInfoOffset).IndexOffset;
        indexCopy.Count = m_BatchManager.GetDrawInfo(lastObject.BatchID, lastObject.DrawInfoOffset).IndexCount;

        m_BufferManager.CopyRegion(vertCopy);
        m_BufferManager.CopyRegion(indexCopy);

        lastObject.VertexOffset = object.VertexOffset;
        m_BatchManager.GetDrawInfo(lastObject.BatchID, lastObject.DrawInfoOffset).IndexOffset = m_BatchManager.GetDrawInfo(object.BatchID, object.DrawInfoOffset).IndexOffset;

        Quilt::Mesh& mesh = m_MeshManager.GetMeshData(lastObject.MeshHandle);
        std::vector<unsigned int> relocatedIndices = mesh.Indices;

        for(unsigned int& index : relocatedIndices)
        {
            index += object.VertexOffset;
        }

        m_BufferManager.PopulateBuffer(indexHandle, relocatedIndices.data(), indexCopy.Count, indexCopy.WriteOffset);

        unsigned int lastDrawInfo = lastObject.DrawInfoOffset;
        unsigned int drawInfo = object.DrawInfoOffset;

        m_BatchManager.GetBatch(object.BatchID).DrawInfos[drawInfo] = m_BatchManager.GetBatch(lastObject.BatchID).DrawInfos[lastDrawInfo];

        lastObject.DrawInfoOffset = drawInfo;
    }

    m_BatchManager.GetBatch(removedBatchID).DrawInfos.pop_back();

    unsigned int vertHandle = m_BatchManager.GetVertexBufferHandle(removedBatchID);
    unsigned int indexHandle = m_BatchManager.GetIndexBufferHandle(removedBatchID);
    m_BufferManager.RemoveRegion(vertHandle, removedVertexCount);
    m_BufferManager.RemoveRegion(indexHandle, removedIndexCount);

    if(m_BufferManager.IsBufferEmpty(vertHandle) && m_BufferManager.IsBufferEmpty(indexHandle))
    {
        m_BufferManager.RemoveBuffer(vertHandle);
        m_BufferManager.RemoveBuffer(indexHandle);
        m_BatchManager.RemoveBatch(removedBatchID);
    }

    m_RenderManager.RemoveRenderableObject(entityID);
}

unsigned int Quilt::Duvet::CreateCamera(bool isActive, float xScreenPos, float yScreenPos, float xScreenSize, float yScreenSize)
{
    unsigned int cameraID = m_CameraManager.CreateCamera();

    m_CameraManager.ToggleCamera(cameraID, isActive);
    m_CameraManager.SetCameraProjection(cameraID, Quilt::Projection::Orthographic);
    m_CameraManager.SetCameraScreenPosition(cameraID, xScreenPos, yScreenPos);
    m_CameraManager.SetCameraScreenSize(cameraID, xScreenSize, yScreenSize);
    m_CameraManager.SetCameraFOV(cameraID, 90.0f);
    m_CameraManager.SetCameraZoom(cameraID, 5.0f);

    return cameraID;
}

void Quilt::Duvet::UpdateCamera(unsigned int cameraHandle, Pillow::Transform& transform)
{
    m_CameraManager.UpdateAspectRatio(cameraHandle);
    m_CameraManager.UpdateCameraTransform(cameraHandle, transform);
}

void Quilt::Duvet::RemoveCamera(unsigned int& cameraHandle)
{
    m_CameraManager.RemoveCamera(cameraHandle);
}

int Quilt::Duvet::CreateTexture(uint64_t entityID, const std::string texturePath, const TextureFiltering filter)
{
    //TODO: check if entity has Renderable
    if(!m_RenderManager.HasRenderableObject(entityID))
    {
        //TODO: Figure out a way to make a renderable not render if there is no data
        //m_RenderManager.CreateRenderableObject(entityID);
    }

    //TODO: this is only for dynamic would be nice to have this change

    //Load Texture from file
    int slot = m_TextureManager.AddTexture(texturePath, filter);

    Quilt::RenderableObject& object = m_RenderManager.GetRenderableObject(entityID);

    unsigned int vertexOffset = object.VertexOffset;
    unsigned int vertexCount = object.VertexCount;
    unsigned int vertexBufferHandle = m_BatchManager.GetBatch(object.BatchID).VertexBufferHandle;
    unsigned int meshID = object.MeshHandle;

    std::vector<Quilt::Vertex> verts = m_MeshManager.GetMeshData(meshID).Vertices;

    for(Quilt::Vertex& vert : verts)
    {
        vert.TextureID = slot;
    }

    m_BufferManager.PopulateBuffer(vertexBufferHandle, verts.data(), vertexCount, vertexOffset);

    return slot;
};

bool Quilt::Duvet::IsContextValid()
{
    return glewInit() == GLEW_OK;
}

void Quilt::Duvet::Draw()
{
    for (const Quilt::Camera& camera : m_CameraManager.GetAllCameras())
    {
        if (!camera.IsActive)
        {
            continue;
        }

        glm::mat4 view = camera.ViewMatrix;

        GLCall(glViewport(camera.ScreenPosition.XPositionPercent, camera.ScreenPosition.YPositionPercent, camera.ScreenPosition.XSizePercent, camera.ScreenPosition.YSizePercent));

        for (Quilt::Batch currentBatch : m_BatchManager.GetAllBatches())
        {
            if (!glIsProgram(currentBatch.Data.ShaderID))
            {
                LOG_WARN("Batch does not have a valid shader bound moving to next batch");
                continue;
            }

            GLCall(glUseProgram(currentBatch.Data.ShaderID));

            m_ShaderManager.SetUniformMat4f(currentBatch.Data.ShaderID, "u_View", camera.ViewMatrix);
            m_ShaderManager.SetUniformMat4f(currentBatch.Data.ShaderID, "u_Projection", camera.ProjectionMatrix);

            int samplers[32];
            for(int i = 0; i < 32; ++i)
            {
                samplers[i] = i;
            } 

            m_ShaderManager.SetUniform1iv(currentBatch.Data.ShaderID, "u_Textures", 32, samplers);

            m_VertexArrayManager.Bind(currentBatch.VertexArrayHandle);

            for(const Quilt::Texture& texture : m_TextureManager.GetTextures())
            {
                GLCall(glActiveTexture(GL_TEXTURE0 + texture.Slot));
                GLCall(glBindTexture(GL_TEXTURE_2D, texture.Handle));
            }

            switch (currentBatch.Data.Type)
            {
                case Quilt::BatchType::None:
                break;
            
                case Quilt::BatchType::Static:
                    break;
                
                case Quilt::BatchType::Dynamic:

                    for(int i = 0; i < currentBatch.DrawInfos.size(); i++)
                    {
                        Quilt::DrawInfo& drawinfo = currentBatch.DrawInfos[i];

                        m_ShaderManager.SetUniformMat4f(currentBatch.Data.ShaderID, "u_Model", drawinfo.TransformMatrix);

                        GLCall(glDrawElements(GL_TRIANGLES, drawinfo.IndexCount, GL_UNSIGNED_INT, (void*)(drawinfo.IndexOffset * sizeof(unsigned int))));
                    }

                    break;

                case Quilt::BatchType::Instanced:
                    //TODO: 0 needs to be replaced with renderableObject.InstanceSlot
                    GLCall(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_BufferManager.GetBufferStorage().Handles[currentBatch.InstanceBufferHandle]));
                    GLCall(glDrawElementsInstanced(GL_TRIANGLES, currentBatch.DrawInfos[0].IndexCount, GL_UNSIGNED_INT, nullptr, currentBatch.InstanceCount));
                    break;
            }

        }
    }
}

void Quilt::Duvet::Clear()
{
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    glEnable(GL_DEBUG_OUTPUT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}