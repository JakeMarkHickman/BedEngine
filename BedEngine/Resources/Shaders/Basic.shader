#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
    gl_Position = position;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 colour;

void main()
{
    colour = vec4(0.651, 0.086, 0.902, 1.0);
};