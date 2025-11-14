#pragma once

#include <Components/Event/ClickableHovered.h>
#include <Components/Event/ClickableUnhovered.h>
#include <Components/Event/ClickableClicked.h>
#include <Components/Event/ClickableReleased.h>

#include <unordered_set>

namespace Bed
{
    void ClickableSystem(Bed::World& world)
    {
        float aspect = Bed::Window::GetAspectRatio();
        WindowSize winsize = Bed::Window::GetWindowSize();

        for(uint64_t i : world.GetAllEntities())
        {
            //TODO: Make Work with 3D objects
            //TODO: Using Input Component feels weird
            //TODO: If changing texture persistant hovered component makes it impossible to change texture
            if(world.HasComponents<Bed::Clickable, Bed::Transform, Bed::Input, Bed::Anchor>(i))
            {
                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);
                Bed::Input* input = world.GetComponent<Bed::Input>(i);
                Bed::Anchor* anchor = world.GetComponent<Bed::Anchor>(i);

                float anchorXWorld = ((anchor->Position.x * 2.0f) - 1.0f) * aspect;
                float anchorYWorld = (anchor->Position.y * 2.0f) - 1.0f;

                //TODO: take into account rotation
                float x = transform->Position.x;
                float y = transform->Position.y;
                float w = transform->Scale.x / 2;
                float h = transform->Scale.y / 2;

                Pillow::Vector3f newPos = transform->Position + Pillow::Vector3f(anchorXWorld, -anchorYWorld, 0.0f);

                float cursorX = (input->CursorX / winsize.Width) * 2.0f - 1.0f;
                float cursorY = ((winsize.Height - input->CursorY) / winsize.Height) * 2.0f - 1.0f;

                cursorX *= aspect;

                bool isHovering = (cursorX >= newPos.x - w && cursorX <= newPos.x + w &&
                                    cursorY >= newPos.y - w && cursorY <= newPos.y + w);

                if(world.HasComponents<Bed::ClickableUnhovered>(i))
                {
                    world.RemoveComponents<Bed::ClickableUnhovered>(i);
                }

                if(!world.HasComponents<Bed::ClickableUnhovered>(i) && !isHovering)
                {
                    world.RemoveComponents<Bed::ClickableHovered>(i);
                    world.AttachComponents(i, Bed::ClickableUnhovered(input->CursorX, input->CursorY));
                }
                
                if(!world.HasComponents<Bed::ClickableHovered>(i) && isHovering)
                {
                    world.AttachComponents(i, Bed::ClickableHovered(input->CursorX, input->CursorY));
                }

                std::unordered_set<int> currentlyPressed;

                for(int mouse = GLFW_MOUSE_BUTTON_1; mouse <= GLFW_MOUSE_BUTTON_LAST; mouse++)
                {
                    if(input->MouseData[mouse] == Bed::KeyState::Pressed)
                    {
                        currentlyPressed.insert(mouse);
                    }
                }

                if(isHovering)
                {
                    std::unordered_set<int> newlyPressed;
                    for(int button : currentlyPressed)
                    {
                        if(input->PreviousMouseData[button] != Bed::KeyState::Pressed)
                        {
                            newlyPressed.insert(button);
                        }
                    }

                    if (world.HasComponents<Bed::ClickableClicked>(i))
                    {
                        world.RemoveComponents<Bed::ClickableClicked>(i);
                    }
                    
                    if(!newlyPressed.empty())
                    {
                        world.AttachComponents(i, Bed::ClickableClicked(input->CursorX, input->CursorY, newlyPressed));
                    }
                }

                if(isHovering)
                {
                    std::unordered_set<int> released;
                    for(std::pair<const int, Bed::KeyState> button : input->PreviousMouseData)
                    {
                        if(input->PreviousMouseData[button.first] != Bed::KeyState::Released && input->MouseData[button.first] != Bed::KeyState::Pressed)
                        {
                            released.insert(button.first);
                        }
                    }

                    if (world.HasComponents<Bed::ClickableReleased>(i))
                    {
                        world.RemoveComponents<Bed::ClickableReleased>(i);
                    }
                        
                    if(!released.empty())
                    {
                        world.AttachComponents(i, Bed::ClickableReleased(input->CursorX, input->CursorY, released));
                    }
                }
            }
        }
    }
}