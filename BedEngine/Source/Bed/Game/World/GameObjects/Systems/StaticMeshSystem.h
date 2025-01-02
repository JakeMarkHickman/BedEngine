#pragma once

#include <Components/StaticMesh.h>

#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>

//TODO: Remove this
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Bed
{
    void StaticMeshSystem(Bed::ECS& ecs, float deltaTime)
    {
        unsigned int totalVertsBefore = 0;
        unsigned int totalIndicesBefore = 0;

        unsigned int index = 0;
        
        std::vector<Bed::Vertex> allVerts;  // Collect all vertices for dynamic allocation
        std::vector<unsigned int> allIndices;  // Collect all indices for dynamic allocation

        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if (ecs.HasComponents<Bed::StaticMesh>(i))
            {
                Bed::Transform* transform = new Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f));

                Bed::StaticMesh* StaticMesh = ecs.GetComponent<Bed::StaticMesh>(i);

                if(ecs.HasComponents<Bed::Transform>(i)) // Checks for a Transform for renderering
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                const auto& verts = StaticMesh->Mesh.GetVertices();
                const auto& indices = StaticMesh->Mesh.GetIndices();

                std::vector<Bed::Vertex> transformedVerts = verts;
                std::vector<unsigned int> modifiedIndices = indices;

                // Transform calculation
                for (auto& vert : transformedVerts)
                {
                    // Apply the transformation matrix to each vertex position
                    glm::vec4 transformedPosition = transform->GetMatrix() * glm::vec4(vert.m_Position.x, vert.m_Position.y, vert.m_Position.z, 1.0f);  // Matrix-vector multiplication
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

        Bed::shader3D->Bind();
        Bed::vb3D->PopulateBuffer(allVerts.data(), allVerts.size() * sizeof(Bed::Vertex), 0);
        Bed::ib3D->PopulateBuffer(allIndices.data(), allIndices.size() * sizeof(unsigned int), 0);
    }
}