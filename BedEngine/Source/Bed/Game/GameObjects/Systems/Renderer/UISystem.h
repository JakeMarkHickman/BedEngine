#pragma once

#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>

//TODO: change this
#include <Bed/Game/GameObjects/Components/UI/Anchor.h>

namespace Bed
{
    struct UIInstanceData
    {
        glm::mat4 MatTransform;
        float TextureID;
        Pillow::Vector2f UVMin;
        Pillow::Vector2f UVMax;
    };

    void UISystem(Bed::World& world)
    {
        float aspect = Bed::Window::GetAspectRatio();
        WindowSize winsize = Bed::Window::GetWindowSize();

        std::vector<UIInstanceData> instances;

        shaderUI->Bind();
        shaderUI->SetUniformMat4f("u_Projection", glm::orthoLH(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f));
        shaderUI->SetUniformMat4f("u_View", glm::mat4(1.0f));

        for(int i = 0; i < world.GetAllEntities().size(); i++)
        {
            if(world.HasComponents<Bed::UIElement>(i))
            {
                Bed::UIElement* element = world.GetComponent<Bed::UIElement>(i);

                if(!world.HasComponents<Bed::Transform>(i)) // Check for Transform
                {
                    world.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 0.1f));
                }
                if(!world.HasComponents<Bed::Anchor>(i)) //Check for Anchor point
                {
                    world.AttachComponents(i, Bed::Anchor(0.0f));
                }
                if(!world.HasComponents<Bed::Texture>(i))
                {
                    world.AttachComponents(i, Bed::Texture(""));
                }

                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);
                Bed::Anchor* anchor = world.GetComponent<Bed::Anchor>(i);
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                float anchorXWorld = ((anchor->Position.x * 2.0f) - 1.0f) * aspect;
                float anchorYWorld = (anchor->Position.y * 2.0f) - 1.0f;

                UIInstanceData instance;
                instance.MatTransform = transform->GetMatrix();

                instance.MatTransform[3].x += anchorXWorld;
                instance.MatTransform[3].y -= anchorYWorld;

                instance.TextureID = texture->TextureSlot;

                Pillow::Vector2f Min(0.0f, 0.0f);
                Pillow::Vector2f Max(1.0f, 1.0f);

                if(world.HasComponents<Bed::SubTexture>(i))
                {
                    Bed::SubTexture* subTexture = world.GetComponent<Bed::SubTexture>(i);
                    
                    Min = subTexture->UVTopLeft;
                    Max = subTexture->UVBottomRight;
                }

                instance.UVMin = Min;
                instance.UVMax = Max;

                instances.push_back(instance);
            }
        }
        
        Bed::ivbUI->PopulateBuffer(instances.data(), instances.size());
    };
}
