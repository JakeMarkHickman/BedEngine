#pragma once

#include <Bed/GameObjects/Components/RenderComponent.h>
#include <Bed/GameObjects/Components/TransformComponent.h>
#include <Bed/GameObjects/Mesh/Quad.h>
#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>
#include <Bed/Core.h>

//TODO: Remove this
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Bed
{
    void RenderSystem(Bed::ECS& ecs, float deltaTime)
    {
        int index = 0;
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            
            //TODO: Change this as i should be used to check index of a value as
            if (ecs.HasComponents<Bed::Render>(i))
            {
                index++;
                Bed::Transform transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f));

                Bed::Render renderer = ecs.GetComponent<Bed::Render>(i);

                if(ecs.HasComponents<Bed::Transform>(i)) // Checks for a Transform for renderering
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                const auto& verts = renderer.m_Mesh.GetVertices();
                const auto& indices = renderer.m_Mesh.GetIndices();

                // Calculate the offsets for this entity's vertex and index data in the buffers
                size_t vertexOffset = verts.size() * (index - 1) * sizeof(Bed::Vertex);
                size_t indexOffset = indices.size() * (index - 1) * sizeof(unsigned int);

                vb->PopulateBuffer(verts.data(), verts.size() * sizeof(Bed::Vertex), vertexOffset);
                ib->PopulateBuffer(indices.data(), indices.size() * sizeof(unsigned int), indexOffset);
            }
        }
    }
}