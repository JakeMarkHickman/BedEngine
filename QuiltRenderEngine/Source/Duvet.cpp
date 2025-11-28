#include "Duvet.h"

#include <algorithm>

unsigned int Quilt::Duvet::CreateMesh(const std::vector<Quilt::Vertex>& vertices, const std::vector<unsigned int>& indices, const Pillow::Transform* transform)
{
    LOG_DEBUG("Texture Slots ", m_TextureManager.GetTextureSlots());

    //TODO: Make this shader be parsed in rather than hardcoded here with materials
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
        o_FragColour = v_Colour; //texture(u_Textures[int(v_TexID)], v_TexCoord) * v_Colour;
    }
    )";

    unsigned int shaderID = m_ShaderManager.AddShader(vertexShader, fragmentShader);

    Quilt::BatchData data;
    data.ShaderID = shaderID;
    data.Type = BatchType::Dynamic;
    //TODO: use vertex layout too!

    Quilt::Batch& batch = m_BatchManager.GetOrCreateBatch(data);

    unsigned int newBatch = m_BatchManager.NewCreateBatch(16000, 24000, data, transform);

    unsigned int vertOffset = m_BatchManager.GetBatchStorage().VertexCounts[newBatch];
    unsigned int indOffset = m_BatchManager.GetBatchStorage().IndexCounts[newBatch];

    m_BatchManager.PopulateBatchBuffer(newBatch, Quilt::BufferType::Vertex, vertices.data(), vertices.size(), vertOffset);
    m_BatchManager.PopulateBatchBuffer(newBatch, Quilt::BufferType::Index, indices.data(), indices.size(), indOffset);

    m_BatchManager.GetBatchStorage().VertexCounts[newBatch] = vertices.size();
    m_BatchManager.GetBatchStorage().IndexCounts[newBatch] = indices.size();

    uint64_t vertexOffset = batch.VertexCount;
    uint64_t indexOffset = batch.IndexCount;
 
    //TODO: dont need to do this here.
    //Upload vertex Buffer data
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, batch.VertexBuffer.Handle));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, vertexOffset * batch.VertexBuffer.DataSize, vertices.size() * batch.VertexBuffer.DataSize, vertices.data()));

    //Upload index Buffer data
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.IndexBuffer.Handle));
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexOffset * batch.IndexBuffer.DataSize, indices.size() * batch.IndexBuffer.DataSize, indices.data()));

    batch.VertexCount += vertices.size();
    batch.IndexCount += indices.size();
    batch.Transforms.push_back(transform);


    Mesh meshHandle;
    meshHandle.BatchIndex = m_BatchManager.GetBatches().size() - 1;
    meshHandle.LocalIndex = batch.Transforms.size() - 1; 
    meshHandle.VertexOffset = vertexOffset;
    meshHandle.IndexOffset = indexOffset;
    meshHandle.VertexCount = vertices.size();
    meshHandle.IndexCount = indices.size();
    meshHandle.Vertices = vertices;
    meshHandle.Indices = indices;

    LOG_DEBUG("Batch ID: ", meshHandle.BatchIndex);

    m_MeshHandles.push_back(meshHandle);
    unsigned int value = m_MeshHandles.size() - 1;

    return value;
}

void Quilt::Duvet::RemoveMesh(const unsigned int& meshHandle)
{
    Quilt::Mesh& meshToRemove = m_MeshHandles[meshHandle];
    Quilt::Batch& batch = m_BatchManager.GetBatches()[meshToRemove.BatchIndex];

    if(meshToRemove.LocalIndex < batch.Transforms.size())
    {
        LOG_DEBUG("Removing Transform pointer in Quilt");
        batch.Transforms.erase(batch.Transforms.begin() + meshToRemove.LocalIndex);
    }

    meshToRemove = {};
}

unsigned int Quilt::Duvet::CreateCamera(const Pillow::Transform* transform)
{
    Quilt::Camera newCamera;

    newCamera.Transform = transform;

    m_Cameras.emplace_back(newCamera);

    unsigned int value = m_Cameras.size() - 1;
    return value;
}

void Quilt::Duvet::CreateTexture(const std::string texturePath, const TextureFiltering filter, const unsigned int& meshHandle)
{
    //Load Texture from file
    int slot = m_TextureManager.AddTexture(texturePath, filter);

    Quilt::Mesh& mesh = m_MeshHandles[meshHandle];

    const Quilt::Batch& batch = m_BatchManager.GetBatches()[mesh.BatchIndex];

    for(Quilt::Vertex& vert : mesh.Vertices)
    {
        vert.TextureID = slot;
    }

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, batch.VertexBuffer.Handle));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, mesh.VertexOffset * batch.VertexBuffer.DataSize, mesh.Vertices.size() * batch.VertexBuffer.DataSize, mesh.Vertices.data()));
};

void Quilt::Duvet::Draw()
{
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    for (const Quilt::Camera& camera : m_Cameras)
    {
        if(!camera.IsActive)
        {
            LOG_INFO("Camera is not active");
            continue;
        }

        m_BatchManager.DrawBatches(m_ShaderManager, camera.Transform);

        /*for (const Quilt::Batch& batch : m_BatchManager.GetBatches())
        {
            //bind shader from batch
            if(!glIsProgram(batch.Data.ShaderID))
            {
                LOG_WARN("Batch does not have a shader Bound");
                continue;
            }

            GLCall(glUseProgram(batch.Data.ShaderID));
            glm::mat4 proj = glm::orthoLH(1.7777f * -5.0f, -1.7777f * -5.0f, -5.0f, 5.0f, -1.0f, 500.0f); // camera

            glm::vec3 camPos = glm::vec3(camera.Transform->Position.x, camera.Transform->Position.y, camera.Transform->Position.z);
            glm::vec3 targetPos = camPos + glm::vec3(0.0f, 0.0f, 1.0f);
            glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

            glm::mat4 view = glm::lookAtLH(camPos, targetPos, upVec);

            switch (batch.Data.Type)
            {
            case BatchType::None:
                GLCall(glBindVertexArray(batch.Data.VertexLayoutID));
                GLCall(glBindBuffer(GL_ARRAY_BUFFER, batch.VertexBuffer.Handle));
                GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.IndexBuffer.Handle));

                GLCall(glDrawElements(GL_TRIANGLES, batch.IndexCount, GL_UNSIGNED_INT, nullptr));
                break;
            case BatchType::Static:
                
                break;
            case BatchType::Dynamic:
                glm::mat4 model;
                
                for (const Pillow::Transform* transform : batch.Transforms)
                {
                    model = glm::translate(glm::mat4(1.0f), glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z)) *
                            glm::yawPitchRoll(
                                glm::radians(transform->Rotation.y),
                                glm::radians(transform->Rotation.x),
                                glm::radians(transform->Rotation.z)
                            ) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(transform->Scale.x, transform->Scale.y, transform->Scale.z));

                    m_ShaderManager.SetUniformMat4f(batch.Data.ShaderID, "u_Model", model);
                    m_ShaderManager.SetUniformMat4f(batch.Data.ShaderID, "u_View", view);
                    m_ShaderManager.SetUniformMat4f(batch.Data.ShaderID, "u_Projection", proj);

                    int samplers[32];
                    for(int i = 0; i < 32; ++i)
                    {
                        samplers[i] = i;
                    } 

                    m_ShaderManager.SetUniform1iv(batch.Data.ShaderID, "u_Textures", 32, samplers);

                    for(const Quilt::Texture& texture : m_TextureManager.GetTextures())
                    {
                        GLCall(glActiveTexture(GL_TEXTURE0 + texture.Slot));
                        GLCall(glBindTexture(GL_TEXTURE_2D, texture.Handle));
                    }

                    GLCall(glBindVertexArray(batch.Data.VertexLayoutID));
                    GLCall(glBindBuffer(GL_ARRAY_BUFFER, batch.VertexBuffer.Handle));
                    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.IndexBuffer.Handle));

                    GLCall(glDrawElements(GL_TRIANGLES, batch.IndexCount, GL_UNSIGNED_INT, nullptr));
                }
                
                break;
            case BatchType::Instanced:
                
                break;
            }
        }*/
    }
}