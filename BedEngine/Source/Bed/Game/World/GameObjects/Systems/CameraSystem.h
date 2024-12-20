#pragma once

#include <GameObjects/Components/CameraComponent.h>
#include <Math/Transform.h>
#include <Graphics/GraphicVariables.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Bed
{
    void CameraSystem(Bed::ECS& ecs, float deltaTime)
    {
        glm::mat4 vp;
        glm::mat4 model;
        glm::mat4 proj;
        glm::mat4 view;
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::Camera>(i))
            {
                Bed::Camera* cam = ecs.GetComponent<Bed::Camera>(i);

                Bed::Transform* transform = new Bed::Transform(0.0f);

                if(ecs.HasComponents<Bed::Transform>(i))
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                //Bind Shader
                shader->Bind();

                switch(cam->m_RenderType)
                {
                    case Bed::RenderType::Orthographic:
                                        //TODO: Take in Screen Width and Hight
                        proj = glm::ortho(-2.0f * 2, 2.0f * 2, -1.5f * 2, 1.5f * 2, -1.0f, 100.0f); // Camera Screen Size
                        break;
                    case Bed::RenderType::Projection:
                        proj = glm::perspective(55.0f, 4.0f / 3.0f, 0.1f, 100.0f);
                        //TODO: This may need to change when using other renderers
                        proj[1][1] *= -1;
                        break;
                    default:
                                        //TODO: Take in Screen Width and Hight
                        proj = glm::ortho(-2.0f *2, 2.0f*2, -1.5f*2, 1.5f*2, -1.0f, 100.0f);
                        break;
                }

                //Set mvp
                view = glm::translate(glm::mat4(1.0f), glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z)); // Camera Pos
                model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));// model Pos
                vp = proj * view;
                shader->SetUniformMat4f("u_ViewProjection", vp);
                shader->SetUniformMat4f("u_Model", model);
            }
        }
    }
}