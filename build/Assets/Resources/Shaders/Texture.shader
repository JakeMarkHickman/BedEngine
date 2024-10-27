#shader vertex
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Colour;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexID;

layout(location = 4) out vec4 fragColor;

uniform mat4 u_MVP;

out vec4 v_Colour;
out vec2 v_TexCoord;
out float v_TexID;

void main()
{
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    v_Colour = a_Colour;
    v_TexCoord = a_TexCoord;
    v_TexID = a_TexID;
    gl_Position = u_MVP * a_Position;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 o_Colour;

in vec4 v_Colour;
in vec2 v_TexCoord;
in float v_TexID;

uniform sampler2D u_Textures[2];

void main()
{
    int index = int(v_TexID);
    o_Colour = texture(u_Textures[index], v_TexCoord);
}