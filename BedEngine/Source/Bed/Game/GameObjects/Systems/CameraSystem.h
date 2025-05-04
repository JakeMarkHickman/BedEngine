#pragma once

#include <Graphics/GraphicVariables.h>
#include <Platforms/Window.h>

namespace Bed
{
    void CameraSystem(Bed::World& world)
    {
        float aspect = Bed::Window::GetAspectRatio();

        glm::mat4 vp;
        glm::mat4 model;
        glm::mat4 proj;
        glm::mat4 view;

        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Camera>(i))
            {
                Bed::Camera* cam = world.GetComponent<Bed::Camera>(i);

                if(!world.HasComponents<Bed::Transform>(i))
                {
                    world.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);

                switch(cam->ProjectionType)
                {
                    case Bed::ProjectionType::Orthographic:
                        proj = glm::orthoLH(-aspect * cam->Zoom, aspect * cam->Zoom, -1.0f * cam->Zoom, 1.0f * cam->Zoom, -1.0f, 500.0f); // Camera Screen Size
                        break;
                    case Bed::ProjectionType::Perspective:
                        proj = glm::perspectiveLH(glm::radians(cam->FOV), aspect, 0.1f, 100.0f); // Use Left Handed rule
                        break;
                }

                glm::vec3 camPos = glm::vec3(transform->Position.x, transform->Position.y, transform->Position.z);
                glm::vec3 targetPos = camPos + glm::vec3(0.0f, 0.0f, 1.0f);
                glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

                //Set mvp
                view = glm::lookAtLH(camPos, targetPos, upVec);
                model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));// model Pos

                shader3D->Bind();
                shader3D->SetUniformMat4f("u_Projection", proj);
                shader3D->SetUniformMat4f("u_View", view);
                shader3D->SetUniformMat4f("u_Model", model);
                shader3D->SetUniform3f("u_CamPos", transform->Position);

                shader2D->Bind();
                shader2D->SetUniformMat4f("u_Projection", proj);
                shader2D->SetUniformMat4f("u_View", view);
                shader2D->SetUniformMat4f("u_Model", model); // TODO: kept for backup
                shader2D->SetUniform3f("u_CamPos", transform->Position);
            }
        }
    }
}