#pragma once

#include <Bed/Game/World/GameObjects/Components/UIRenderComponent.h>
#include <Math/Transform.h>
#include <Bed/Game/World/GameObjects/Mesh/Quad.h>

#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>
#include <array>

namespace Bed
{
    void UIRenderSystem(Bed::ECS& ecs, float deltaTime)
    {
        unsigned int index = 0;

        std::vector<Bed::Vertex> allVertsUI;  // Collect all vertices for dynamic allocation
        std::vector<unsigned int> allIndicesUI;  // Collect all indices for dynamic allocation
        
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if (ecs.HasComponents<Bed::UIRender>(i))
            {
                shaderUI->Bind();
                index++;

                Bed::Transform transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f));

                Bed::UIRender renderer = ecs.GetComponent<Bed::UIRender>(i);

                if(ecs.HasComponents<Bed::Transform>(i)) // Checks for a Transform for renderering
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                std::array<Bed::Vertex, 4> verts;
                std::array<unsigned int, 6> indices;

                auto q0 = CreateQuad(Bed::Vector2(transform.Position.x, transform.Position.y), Bed::Vector4(1.0f), Bed::Vector2(transform.Scale.x, transform.Scale.y), 0.0f);
                std::copy(std::begin(q0), std::end(q0), verts.begin());

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

                allVertsUI.insert(allVertsUI.end(), verts.begin(), verts.end());
                allIndicesUI.insert(allIndicesUI.end(), indices.begin(), indices.end());

                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));// model Pos

                                //TODO: Take in Screen Width and Hight
                glm::mat4 vp = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
                shaderUI->SetUniformMat4f("u_ViewProjection", vp);
                shaderUI->SetUniformMat4f("u_Model", model);
            }
        }

        shaderUI->Bind();
        vbUI->PopulateBuffer(allVertsUI.data(), allVertsUI.size() * sizeof(Bed::Vertex), 0);
        ibUI->PopulateBuffer(allIndicesUI.data(), allIndicesUI.size() * sizeof(unsigned int), 0);
    }
}