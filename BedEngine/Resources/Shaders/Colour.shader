#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Colour;

uniform mat4 u_MVP;

out vec4 v_Colour;

void main()
{
    v_Colour = a_Colour;
    gl_Position = u_MVP * a_Position;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 o_Colour;

in vec4 v_Colour;

void main()
{
    o_Colour = v_Colour;
}