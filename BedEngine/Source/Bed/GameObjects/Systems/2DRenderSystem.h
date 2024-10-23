#pragma once

#include <Bed/GameObjects/Components/2DRenderComponent.h>
#include <Bed/GameObjects/Components/TransformComponent.h>
#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>
#include <Bed/GameObjects/Mesh/Quad.h>
#include <Bed/Core.h>
#include <iostream>

//TODO: Remove this
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Bed
{
    void TwoDimensionalRenderSystem(Bed::ECS& ecs, float deltaTime)
    {
        int index = 0;
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            
            //TODO: Change this as i should be used to check index of a value as
            if (ecs.HasComponents<Bed::TwoDimensionalRender>(i))
            {
                index++;
                Bed::Transform transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f));

                Bed::TwoDimensionalRender renderer = ecs.GetComponent<Bed::TwoDimensionalRender>(i);

                if(ecs.HasComponents<Bed::Transform>(i)) // Checks for a Transform for renderering
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                Bed::Vertex verts[4];
                unsigned int indices[6];
                size_t vertexOffset = (sizeof(verts) / sizeof(Bed::Vertex)) * (index - 1) * sizeof(Bed::Vertex);
                size_t indexOffset = sizeof(indices) * (index - 1) * sizeof(unsigned int);

                //TODO: Do rendering stuffs
                auto q0 = CreateQuad(transform.m_Position, Bed::Vector4(0.18f, 0.6f, 0.95f, 1.0f), transform.m_Scale, 0.0f);
                memcpy(verts, q0.data(), q0.size() * sizeof(Bed::Vertex));

                unsigned int baseIndex = 4 * (index - 1);
                unsigned int indexCount = 0;
                for (int i = 0; i < sizeof(verts) / sizeof(Bed::Vertex); i += 4) 
                {
                    // First triangle (0, 1, 2)
                    indices[indexCount++] = baseIndex;
                    indices[indexCount++] = baseIndex + 1;
                    indices[indexCount++] = baseIndex + 2;

                    // Second triangle (2, 1, 3)
                    indices[indexCount++] = baseIndex + 2;
                    indices[indexCount++] = baseIndex + 1;
                    indices[indexCount++] = baseIndex + 3;
                }

                vb->PopulateBuffer(verts, sizeof(verts), vertexOffset);
                ib->PopulateBuffer(indices, sizeof(indices), indexOffset);
            }
        }
    }
}