#shader vertex
#version 450 core

//Vector
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec4 a_Colour;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in float a_TexID;

//Model view Projection Matrix
uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

out vec4 v_Colour;
out vec2 v_TexCoord;
out float v_TexID;

void main()
{
    v_Colour = a_Colour;
    v_TexCoord = a_TexCoord;
    v_TexID = a_TexID;
    gl_Position = u_ViewProjection * u_Model * a_Position;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 o_FragColour;

//Vector
in vec4 v_Colour;
in vec2 v_TexCoord;
in float v_TexID;

//Texture
uniform sampler2D u_Textures[2];

void main()
{
    int index = int(v_TexID);
    vec3 result = vec3(texture(u_Textures[index], v_TexCoord) * v_Colour);

    //Output
    o_FragColour = vec4(result, 1.0);
}