#pragma once

#include <GameObjects/Components/RenderComponent.h>
#include <Math/Transform.h>
#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>

//TODO: Remove this
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Bed
{
    void RenderSystem(Bed::ECS& ecs, float deltaTime)
    {
        unsigned int totalVertsBefore = 0;
        unsigned int totalIndicesBefore = 0;
        
        std::vector<Bed::Vertex> allVerts;  // Collect all vertices for dynamic allocation
        std::vector<unsigned int> allIndices;  // Collect all indices for dynamic allocation

        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            //TODO: Change this as i should be used to check index of a value as
            if (ecs.HasComponents<Bed::Render>(i))
            {
                Bed::Transform transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f));

                Bed::Render renderer = ecs.GetComponent<Bed::Render>(i);

                if(ecs.HasComponents<Bed::Transform>(i)) // Checks for a Transform for renderering
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                const auto& verts = renderer.m_Mesh.GetVertices();
                const auto& indices = renderer.m_Mesh.GetIndices();

                std::vector<Bed::Vertex> transformedVerts = verts;
                std::vector<unsigned int> modifiedIndices = indices;

                // Transform calculation
                for (auto& vert : transformedVerts)
                {
                    // Apply the transformation matrix to each vertex position
                    glm::vec4 transformedPosition = transform.GetMatrix() * glm::vec4(vert.m_Position.x, vert.m_Position.y, vert.m_Position.z, 1.0f);  // Matrix-vector multiplication
                    vert.m_Position = Bed::Vector3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
                }

                for (auto& ind : modifiedIndices)
                {
                    ind += totalVertsBefore;
                }

                allVerts.insert(allVerts.end(), transformedVerts.begin(), transformedVerts.end());
                allIndices.insert(allIndices.end(), modifiedIndices.begin(), modifiedIndices.end());

                totalVertsBefore += verts.size();
                totalIndicesBefore += indices.size();
            }
        }

        vb->PopulateBuffer(allVerts.data(), allVerts.size() * sizeof(Bed::Vertex), 0);
        ib->PopulateBuffer(allIndices.data(), allIndices.size() * sizeof(unsigned int), 0);
    }
}