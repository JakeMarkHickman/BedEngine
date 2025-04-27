#pragma once

#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>

//TODO: change this
#include <Bed/Game/GameObjects/Components/UI/Anchor.h>

namespace Bed
{
    void UISystem(Bed::World& world)
    {
        //TODO: ui ugly refactor and ui moves based on all elements

        float aspect = Bed::Window::GetAspectRatio();
        WindowSize winsize = Bed::Window::GetWindowSize();

        Bed::Vertex v0;
        v0.m_Position = { -0.5f, -0.5f, 0.0f };
        v0.m_Normal = { 0.0f, 0.0f, 0.0f };
        v0.m_Colour = { Bed::Vector4(1.0f, 1.0f, 1.0f, 1.0f) };
        v0.m_TexCoords = { 0.0f,  0.0f };
        v0.m_TexID = 0;

        Bed::Vertex v1;
        v1.m_Position = { 0.5f, -0.5f, 0.0f };
        v1.m_Normal = { 0.0f, 0.0f, 0.0f };
        v1.m_Colour = { Bed::Vector4(1.0f, 1.0f, 1.0f, 1.0f) };
        v1.m_TexCoords = { 1.0f,  0.0f };
        v1.m_TexID = 0;

        Bed::Vertex v2;
        v2.m_Position = { 0.5f, 0.5f, 0.0f };
        v2.m_Normal = { 0.0f, 0.0f, 0.0f };
        v2.m_Colour = { Bed::Vector4(1.0f, 1.0f, 1.0f, 1.0f) };
        v2.m_TexCoords = { 1.0f,  1.0f };
        v2.m_TexID = 0;

        Bed::Vertex v3;
        v3.m_Position = { -0.5f, 0.5f, 0.0f };
        v3.m_Normal = { 0.0f, 0.0f, 0.0f };
        v3.m_Colour = { Bed::Vector4(1.0f, 1.0f, 1.0f, 1.0f) };
        v3.m_TexCoords = { 0.0f,  1.0f };
        v3.m_TexID = 0;

        std::vector<Bed::Vertex> verts = { v0, v1, v2, v3 };
        std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

        unsigned int totalVertsBefore = 0;
        unsigned int totalIndicesBefore = 0;

        unsigned int index = 0;
        
        std::vector<Bed::Vertex> allVerts;  // Collect all vertices for dynamic allocation
        std::vector<unsigned int> allIndices;  // Collect all indices for dynamic allocation

        shaderUI->Bind();

        //TODO: Use screen size
        shaderUI->SetUniformMat4f("u_Projection", glm::orthoLH(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f));
        shaderUI->SetUniformMat4f("u_View", glm::mat4(1.0f));
        shaderUI->SetUniformMat4f("u_Model", glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::UIElement>(i))
            {
                Bed::UIElement* element = world.GetComponent<Bed::UIElement>(i);

                if(!world.HasComponents<Bed::Transform>(i)) // Check for Transform
                {
                    world.AttachComponents(i, Bed::Transform(1.0f, 0.0f, 0.1f));
                }
                if(!world.HasComponents<Bed::Anchor>(i)) //Check for Anchor point
                {
                    world.AttachComponents(i, Bed::Anchor(0.0f));
                }

                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);
                Bed::Anchor* anchor = world.GetComponent<Bed::Anchor>(i);

                float anchorXWorld = ((anchor->Position.x * 2.0f) - 1.0f) * aspect;
                float anchorYWorld = (anchor->Position.y * 2.0f) - 1.0f;

                std::vector<Bed::Vertex> transformedVerts = verts;
                std::vector<unsigned int> modifiedIndices = indices;

                // Transform calculation
                for (auto& vert : transformedVerts)
                {
                    // Apply the transformation matrix to each vertex position
                    glm::vec4 transformedPosition = transform->GetMatrix() * glm::vec4(vert.m_Position.x, vert.m_Position.y, 0.0f, 1.0f);  // Matrix-vector multiplication

                    transformedPosition.x += anchorXWorld;
                    transformedPosition.y -= anchorYWorld;

                    vert.m_Position = Bed::Vector3(transformedPosition.x, transformedPosition.y, 0.0f);
                    
                    //TODO: change this to texture component
                    if(world.HasComponents<Bed::Texture>(i))
                    {
                        Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                        vert.m_TexID = texture->TextureSlot;
                    }
                }

                for (auto& ind : modifiedIndices)
                {
                    ind += totalVertsBefore;
                }

                //TODO: rendering only works in one world at a time as it starts to remove entites from another world
                //This is probably due to how the buffers work
                //To combat this systems could operate on every world

                allVerts.insert(allVerts.end(), transformedVerts.begin(), transformedVerts.end());
                allIndices.insert(allIndices.end(), modifiedIndices.begin(), modifiedIndices.end());

                totalVertsBefore += verts.size();
                totalIndicesBefore += indices.size();
            }
        }

        Bed::vbUI->PopulateBuffer(allVerts.data(), allVerts.size(), 0);
        Bed::ibUI->PopulateBuffer(allIndices.data(), allIndices.size(), 0);
    };
}
