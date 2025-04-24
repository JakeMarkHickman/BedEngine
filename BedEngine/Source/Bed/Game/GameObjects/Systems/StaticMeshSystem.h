#pragma once

#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>

//TODO: Remove this
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Bed
{
    //TODO: This needs to look much better as textures and location currently clash
    //TODO: highly inefficent batch entities based on model
    //TODO: Make cleaner as there is alot of uploading to the GPU currently
    void StaticMeshSystem(Bed::World& world)
    {
        unsigned int totalVertsBefore = 0;
        unsigned int totalIndicesBefore = 0;

        unsigned int index = 0;
        
        std::vector<Bed::Vertex> allVerts;  // Collect all vertices for dynamic allocation
        std::vector<unsigned int> allIndices;  // Collect all indices for dynamic allocation

        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if (world.HasComponents<Bed::StaticMesh>(i))
            {
                Bed::StaticMesh* StaticMesh = world.GetComponent<Bed::StaticMesh>(i);

                if(!world.HasComponents<Bed::Transform>(i))
                {
                    world.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);
                
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

        Bed::shader3D->Bind();
        Bed::vb3D->PopulateBuffer(allVerts.data(), allVerts.size(), 0);
        Bed::ib3D->PopulateBuffer(allIndices.data(), allIndices.size(), 0);
    }
}