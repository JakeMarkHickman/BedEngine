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

void Quilt::Duvet::CreateRenderableObject(uint64_t entityID, unsigned int meshID, unsigned int shaderID, const Pillow::Transform* transform)
{
    unsigned int batchHandle;

    Quilt::Mesh& mesh = m_MeshManager.GetMeshData(meshID);
    Quilt::BatchData data;
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
        unsigned int indexBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Index, sizeof(unsigned int), indexCount);

        batchHandle = m_BatchManager.CreateBatchHandle(vertexBufferHandle, indexBufferHandle, data);
    }

    unsigned int vertexBufferHandle = m_BatchManager.GetVertexBufferHandle(batchHandle);
    unsigned int indexBufferHandle = m_BatchManager.GetIndexBufferHandle(batchHandle);

    //Create the batch and assign data
    DrawInfo info;
    info.Transform = transform;
    info.IndexCount = mesh.Indices.size();
    info.IndexOffset = m_BufferManager.GetOccupiedCount(indexBufferHandle);

    unsigned int drawInfoOffset = m_BatchManager.AddDrawInfo(batchHandle, info);

    Quilt::RenderableObject object;
    object.BatchID = batchHandle;
    object.DrawInfoOffset = drawInfoOffset;
    object.VertexOffset = m_BufferManager.GetOccupiedCount(vertexBufferHandle);
    object.IndexOffset = m_BufferManager.GetOccupiedCount(indexBufferHandle);
    object.VertexCount = mesh.Vertices.size();
    object.IndexCount = mesh.Indices.size();
    object.MeshHandle = meshID;

    LOG_DEBUG("CreateRenderableObject Entity: ", entityID, " VertexOffset: ", object.VertexOffset);

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

void Quilt::Duvet::UpdateRenderableObjectTransform(uint64_t entityID, Pillow::Transform& transform)
{

}

void Quilt::Duvet::RemoveRenderableObject(uint64_t entityID)
{
    Quilt::RenderableObject& object = m_RenderManager.GetRenderableObject(entityID);
    unsigned int lastEntity = m_RenderManager.GetLastRenderableEntity();

    if(lastEntity != entityID)
    {
        Quilt::RenderableObject& lastObject = m_RenderManager.GetRenderableObject(lastEntity);

        CopyInfo vertCopy;
        vertCopy.ReadBuffer = m_BatchManager.GetVertexBufferHandle(lastObject.BatchID);
        vertCopy.WriteBuffer = m_BatchManager.GetVertexBufferHandle(object.BatchID);
        vertCopy.ReadOffset = lastObject.VertexOffset;
        vertCopy.WriteOffset = object.VertexOffset;
        vertCopy.Count = lastObject.VertexCount;
        
        CopyInfo indexCopy;
        indexCopy.ReadBuffer = m_BatchManager.GetIndexBufferHandle(lastObject.BatchID);
        indexCopy.WriteBuffer = m_BatchManager.GetIndexBufferHandle(object.BatchID);
        indexCopy.ReadOffset = lastObject.IndexOffset;
        indexCopy.WriteOffset = object.IndexOffset;
        indexCopy.Count = lastObject.IndexCount;

        m_BufferManager.CopyRegion(vertCopy);
        m_BufferManager.CopyRegion(indexCopy);

        lastObject.VertexOffset = object.VertexOffset;
        lastObject.IndexOffset = object.IndexOffset;
    }

    //TODO: carry on here

    unsigned int vertHandle = m_BatchManager.GetVertexBufferHandle(object.BatchID);

    m_BufferManager.IsBufferEmpty(vertHandle);

    m_RenderManager.RemoveRenderableObject(entityID);

    /*unsigned int batchID = m_MeshManager.GetMeshBatchID(meshHandle);
    unsigned int vertBufferID = m_BatchManager.GetIndexBufferHandle(batchID);
    unsigned int indexBufferID = m_BatchManager.GetVertexBufferHandle(batchID);

    m_BufferManager.RemoveBuffer(vertBufferID);
    m_BufferManager.RemoveBuffer(indexBufferID);

    //TODO: when there is storage buffers loop through all the buffers to remove

    //check if batch is empty
    if (m_BatchManager.IsBatchEmpty(batchID))
    {
        m_BatchManager.RemoveBatch(batchID); //Remove the batch if Empty
    }

    m_MeshManager.RemoveMesh(meshHandle);*/
}

unsigned int Quilt::Duvet::CreateCamera(const Pillow::Transform* transform, bool isActive, float xScreenPos, float yScreenPos, float xScreenSize, float yScreenSize)
{
    unsigned int cameraID = m_CameraManager.CreateCamera(transform);

    m_CameraManager.ToggleCamera(cameraID, isActive);
    m_CameraManager.SetCameraProjection(cameraID, Quilt::Projection::Orthographic);
    m_CameraManager.SetCameraScreenPosition(cameraID, xScreenPos, yScreenPos);
    m_CameraManager.SetCameraScreenSize(cameraID, xScreenSize, yScreenSize);
    m_CameraManager.SetCameraFOV(cameraID, 90.0f);
    m_CameraManager.SetCameraZoom(cameraID, 5.0f);

    return cameraID;
}

void Quilt::Duvet::RemoveCamera(unsigned int& cameraHandle)
{
    m_CameraManager.RemoveCamera(cameraHandle);
}

void Quilt::Duvet::CreateTexture(uint64_t entityID, const std::string texturePath, const TextureFiltering filter)
{
    //TODO: check if entity has Renderable
    if(!m_RenderManager.HasRenderableObject(entityID))
    {
        //TODO: Figure out a way to make a renderable not render if there is no data
        //m_RenderManager.CreateRenderableObject(entityID);
    }

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

        float xSizePercent = camera.ScreenBounds.XSize * WindowWidth;
        float ySizePercent = camera.ScreenBounds.YSize * WindowHeight;

        float xPosPercent = camera.ScreenBounds.XPosition * WindowWidth;
        float yPosPercent = camera.ScreenBounds.YPosition * WindowHeight;

        float aspect = xSizePercent / ySizePercent;

        float left = -camera.Zoom * aspect;
        float right = camera.Zoom * aspect;
        float bottom = -camera.Zoom;
        float top = camera.Zoom;

        glm::mat4 proj = glm::orthoLH(left, right, bottom, top, -1.0f, 500.0f); // camera
        glm::vec3 camPos = glm::vec3(camera.Transform->Position.x, camera.Transform->Position.y, camera.Transform->Position.z);
        glm::vec3 targetPos = camPos + glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 view = glm::lookAtLH(camPos, targetPos, upVec);

        GLCall(glViewport(xPosPercent, yPosPercent, xSizePercent, ySizePercent));

        for (Quilt::Batch currentBatch : m_BatchManager.GetAllBatches())
        {
            if (!glIsProgram(currentBatch.Data.ShaderID))
            {
                LOG_WARN("Batch does not have a valid shader bound moving to next batch");
                continue;
            }

            GLCall(glUseProgram(currentBatch.Data.ShaderID));

            switch (currentBatch.Data.Type)
            {
                case Quilt::BatchType::None:
                break;
            
                case Quilt::BatchType::Static:
                    break;
                
                case Quilt::BatchType::Dynamic:
                    
                    m_ShaderManager.SetUniformMat4f(currentBatch.Data.ShaderID, "u_View", view);
                    m_ShaderManager.SetUniformMat4f(currentBatch.Data.ShaderID, "u_Projection", proj);

                    int samplers[32];
                    for(int i = 0; i < 32; ++i)
                    {
                        samplers[i] = i;
                    } 

                    m_ShaderManager.SetUniform1iv(currentBatch.Data.ShaderID, "u_Textures", 32, samplers);

                    for(const Quilt::Texture& texture : m_TextureManager.GetTextures())
                    {
                        GLCall(glActiveTexture(GL_TEXTURE0 + texture.Slot));
                        GLCall(glBindTexture(GL_TEXTURE_2D, texture.Handle));
                    }

                    for(int i = 0; i < currentBatch.DrawInfos.size(); i++)
                    {
                        Quilt::DrawInfo& drawinfo = currentBatch.DrawInfos[i];
                        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(drawinfo.Transform->Position.x, drawinfo.Transform->Position.y, drawinfo.Transform->Position.z)) *
                            glm::yawPitchRoll(
                                glm::radians(drawinfo.Transform->Rotation.y),
                                glm::radians(drawinfo.Transform->Rotation.x),
                                glm::radians(drawinfo.Transform->Rotation.z)
                            ) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(drawinfo.Transform->Scale.x, drawinfo.Transform->Scale.y, drawinfo.Transform->Scale.z));

                        m_ShaderManager.SetUniformMat4f(currentBatch.Data.ShaderID, "u_Model", model);

                        //unsigned int indexCount  = 6;
                        //unsigned int indexOffset = i * indexCount;

                        GLCall(glDrawElements(GL_TRIANGLES, drawinfo.IndexCount, GL_UNSIGNED_INT, (void*)(drawinfo.IndexOffset * sizeof(unsigned int))));
                    }

                    break;

                case Quilt::BatchType::Instanced:
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