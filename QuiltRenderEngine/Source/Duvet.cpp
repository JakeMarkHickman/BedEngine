#include "Duvet.h"

#include <algorithm>

unsigned int Quilt::Duvet::CreateMesh(const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices, const Pillow::Transform* transform)
{
    LOG_INFO("Device Texture Slots ", m_TextureManager.GetTextureSlots());

    //TODO: Make this shader be parsed in with materials rather than hardcoded here
    std::string vertexShader = R"(
    #version 450 core 
    layout(location = 0) in vec4 a_Position;
    layout(location = 1) in vec3 a_Normal;
    layout(location = 2) in vec4 a_Colour;
    layout(location = 3) in vec2 a_TexCoord;
    layout(location = 4) in float a_TexID;

    uniform mat4 u_View;
    uniform mat4 u_Projection;
    uniform mat4 u_Model;

    out vec4 v_Pos;
    out vec3 v_Normal;
    out vec4 v_Colour;
    out vec2 v_TexCoord;
    flat out float v_TexID;

    vec4 mvp(vec4 pos)
    {
        return u_Projection * u_View * (u_Model * pos);
    }

    void main()
    {
        v_Pos = u_Model * a_Position;
        v_Normal = a_Normal;
        v_Colour = a_Colour;
        v_TexCoord = a_TexCoord;
        v_TexID = a_TexID;

        gl_Position = mvp(a_Position);
    }
    )";

    std::string fragmentShader = R"(
    #version 450 core
    in vec4 v_Pos;
    in vec3 v_Normal;
    in vec4 v_Colour;
    in vec2 v_TexCoord;
    flat in float v_TexID;

    uniform sampler2D u_Textures[32];

    layout(location = 0) out vec4 o_FragColour;

    void main()
    {
        o_FragColour = texture(u_Textures[int(v_TexID)], v_TexCoord) * v_Colour;
    }
    )";

    unsigned int shaderID = m_ShaderManager.AddShader(vertexShader, fragmentShader);

    Quilt::BatchData data;
    data.ShaderID = shaderID;
    data.Type = BatchType::Dynamic;
    //TODO: use vertex layout too!

    //Create the buffers
    unsigned int vertexCount = 16000;
    unsigned int indexCount = 24000;
    unsigned int vertexBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Vertex, sizeof(Quilt::Vertex), vertexCount);
    unsigned int indexBufferHandle = m_BufferManager.CreateBuffer(Quilt::BufferType::Index, sizeof(unsigned int), indexCount);

    //Create the batch and assign data
    unsigned int batchHandle = m_BatchManager.GetOrCreateBatch(vertexBufferHandle, indexBufferHandle, data);
    unsigned int transformOffset = m_BatchManager.AddTransform(batchHandle, transform);

    //Populate buffers
    m_BufferManager.PopulateBuffer(m_BatchManager.GetVertexBufferHandle(batchHandle), vertices.data(), vertices.size(), m_BatchManager.GetVertexCount(batchHandle));
    m_BufferManager.PopulateBuffer(m_BatchManager.GetIndexBufferHandle(batchHandle), indices.data(), indices.size(), m_BatchManager.GetIndexCount(batchHandle));

    //Create the Mesh Handle
    unsigned int newMesh = m_MeshManager.CreateMeshHandle();
    m_MeshManager.SetMeshBatchID(newMesh, batchHandle);
    m_MeshManager.SetMeshTransformOffset(newMesh, transformOffset);
    m_MeshManager.SetMeshVertexOffset(newMesh, m_BatchManager.GetVertexCount(batchHandle));
    m_MeshManager.SetMeshIndicesOffset(newMesh, m_BatchManager.GetIndexCount(batchHandle));
    m_MeshManager.SetMeshVertexCount(newMesh, vertices.size());
    m_MeshManager.SetMeshIndexCount(newMesh, indices.size());
    m_MeshManager.SetMeshVertices(newMesh, vertices);
    m_MeshManager.SetMeshIndices(newMesh, indices);

    return newMesh;
}

void Quilt::Duvet::RemoveMesh(unsigned int& meshHandle)
{
    unsigned int batchID = m_MeshManager.GetMeshBatchID(meshHandle);
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

    m_MeshManager.RemoveMesh(meshHandle);
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

void Quilt::Duvet::CreateTexture(const std::string texturePath, const TextureFiltering filter, unsigned int& meshHandle)
{
    //Load Texture from file
    int slot = m_TextureManager.AddTexture(texturePath, filter);

    unsigned int batchHandle = m_MeshManager.GetMeshBatchID(meshHandle);
    unsigned int vertexOffset = m_MeshManager.GetMeshVertexOffset(meshHandle);
    unsigned int vertexCount = m_MeshManager.GetMeshVertexCount(meshHandle);
    unsigned int vertexBufferHandle = m_BatchManager.GetBatch(batchHandle).VertexBufferHandle;

    for(Quilt::Vertex& vert : m_MeshManager.GetMeshVertices(meshHandle))
    {
        vert.TextureID = slot;
    }

    m_BufferManager.PopulateBuffer(vertexBufferHandle, m_MeshManager.GetMeshVertices(meshHandle).data(), vertexCount, vertexOffset);
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
                    glm::mat4 model;
                    for (const Pillow::Transform* transform : currentBatch.Transforms)
                    {
                        model = glm::translate(glm::mat4(1.0f), glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z)) *
                                glm::yawPitchRoll(
                                    glm::radians(transform->Rotation.y),
                                    glm::radians(transform->Rotation.x),
                                    glm::radians(transform->Rotation.z)
                                ) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(transform->Scale.x, transform->Scale.y, transform->Scale.z));

                        m_ShaderManager.SetUniformMat4f(currentBatch.Data.ShaderID, "u_Model", model);
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

                        GLCall(glBindVertexArray(currentBatch.Data.VertexLayoutID));
                        m_BufferManager.BindBuffer(currentBatch.VertexBufferHandle);
                        m_BufferManager.BindBuffer(currentBatch.IndexBufferHandle);

                        //TODO: This draw seems tedious ideally this would be non-trivial -> m_BatchManager.GetBufferManager().GetBufferStorage().DataCounts[currentBatch.IndexBufferHandle]
                        GLCall(glDrawElements(GL_TRIANGLES, m_BufferManager.GetBufferStorage().DataCounts[currentBatch.IndexBufferHandle], GL_UNSIGNED_INT, nullptr));
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