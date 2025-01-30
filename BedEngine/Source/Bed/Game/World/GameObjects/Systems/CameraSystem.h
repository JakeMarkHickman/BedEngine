#pragma once

#include <Components/Camera.h>

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

                if(!ecs.HasComponents<Bed::Transform>(i))
                {
                    ecs.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                Bed::Transform* transform = ecs.GetComponent<Bed::Transform>(i);

                //Bind Shader
                shader3D->Bind();

                switch(cam->ProjectionType)
                {
                    case Bed::ProjectionType::Orthographic:
                                        //TODO: Take in Screen Width and Hight
                        proj = glm::orthoLH(-2.0f * 2, 2.0f * 2, -1.5f * 2, 1.5f * 2, 0.1f, 500.0f); // Camera Screen Size
                        break;
                    case Bed::ProjectionType::Perspective:
                        proj = glm::perspectiveLH(55.0f, 4.0f / 3.0f, 0.1f, 100.0f); // Use Left Handed rule
                        //TODO: This may need to change when using other renderers
                        proj[1][1] *= -1; // without this y value is flipped and 1 is down and -1 is up
                        proj[0][0] *= -1; // without this X value is flipped and 1 is down and -1 is up
                        break;
                }

                glm::vec3 camPos = glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z);
                glm::vec3 targetPos = camPos + glm::vec3(0.0f, 0.0f, 1.0f);
                glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

                //Set mvp
                view = glm::lookAtLH(camPos, targetPos, upVec);
                //view = glm::translate(glm::mat4(1.0f), glm::vec3(transform->Position.x, transform->Position.y, -transform->Position.z)); // Camera Pos
                model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));// model Pos
                shader3D->SetUniformMat4f("u_Projection", proj);
                shader3D->SetUniformMat4f("u_View", view);
                shader3D->SetUniformMat4f("u_Model", model);
                shader3D->SetUniform3f("u_CamPos", transform->Position);
            }
        }
    }
}