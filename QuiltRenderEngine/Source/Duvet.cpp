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

    //Create the batch and assign data
    unsigned int batchHandle = m_BatchManager.GetOrCreateBatch(16000, 24000, data);

    //Create the Mesh Handle allowing for a 
    unsigned int newMesh = m_MeshManager.CreateMeshHandle();
    m_MeshManager.SetMeshBatchID(newMesh, batchHandle);
    //m_MeshManager.SetMeshTransformOffset(newMesh, );


    unsigned int newMesh = m_BatchManager.CreateMesh(data, vertices, indices, transform);

    return newMesh;
}

void Quilt::Duvet::RemoveMesh(const unsigned int& meshHandle)
{
    m_BatchManager.RemoveMesh(meshHandle);

    //Quilt::Mesh& meshToRemove = m_MeshHandles[meshHandle];
    //Quilt::Batch& batch = m_BatchManager.GetBatches()[meshToRemove.BatchIndex];

    //LOG_DEBUG("Removing batch: ", meshToRemove.BatchIndex);
    //m_BatchManager.RemoveBatch(meshToRemove.BatchIndex);

    //if(meshToRemove.LocalIndex < batch.Transforms.size())
    //{
    //    LOG_DEBUG("Removing Transform pointer in Quilt");
    //    batch.Transforms.erase(batch.Transforms.begin() + meshToRemove.LocalIndex);
    //}

    //meshToRemove = {};
}

unsigned int Quilt::Duvet::CreateCamera(const Pillow::Transform* transform, bool isActive, float xScreenPos, float yScreenPos, float xScreenSize, float yScreenSize)
{
    unsigned int cameraID = m_CameraManager.CreateCamera(transform);

    m_CameraManager.ToggleCamera(cameraID, isActive);
    m_CameraManager.SetCameraProjection(cameraID, Quilt::ProjectionType::Orthographic);
    m_CameraManager.SetCameraScreenPosition(cameraID, xScreenPos, yScreenPos);
    m_CameraManager.SetCameraScreenSize(cameraID, xScreenSize, yScreenSize);

    return cameraID;
}

void Quilt::Duvet::CreateTexture(const std::string texturePath, const TextureFiltering filter, const unsigned int& meshHandle)
{
    /*//Load Texture from file
    int slot = m_TextureManager.AddTexture(texturePath, filter);

    Quilt::Mesh& mesh = m_MeshHandles[meshHandle];

    const Quilt::Batch& batch = m_BatchManager.GetBatches()[mesh.BatchIndex];

    for(Quilt::Vertex& vert : mesh.Vertices)
    {
        vert.TextureID = slot;
    }

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, batch.VertexBuffer.Handle));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, mesh.VertexOffset * batch.VertexBuffer.DataSize, mesh.Vertices.size() * batch.VertexBuffer.DataSize, mesh.Vertices.data()));
    */
};

void Quilt::Duvet::Draw()
{
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    for (unsigned int camera : m_CameraManager.GetAllCameras())
    {
        if(!m_CameraManager.IsCameraActive(camera))
        {
            LOG_INFO("Camera is not active");
            continue;
        }

        CameraScreenSizeBounds bounds = m_CameraManager.GetCameraScreen(camera);

        float xSizePercent = bounds.XSize * WindowWidth;
        float ySizePercent = bounds.YSize * WindowHeight;

        float xPosPercent = bounds.XPosition * WindowWidth;
        float yPosPercent = bounds.YPosition * WindowHeight;

        GLCall(glViewport(xPosPercent, yPosPercent, xSizePercent, ySizePercent));

        m_BatchManager.DrawBatches(m_ShaderManager, m_CameraManager.GetCameraTransform(camera), xSizePercent, ySizePercent);
    }
}