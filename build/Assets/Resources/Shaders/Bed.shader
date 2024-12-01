#shader vertex
#version 450 core

//Vector
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Colour;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexID;

//Model view Projection Matrix
uniform mat4 u_MVP;

out vec4 v_Colour;
out vec2 v_TexCoord;
out float v_TexID;

void main()
{
    v_Colour = a_Colour;
    v_TexCoord = a_TexCoord;
    v_TexID = a_TexID;
    gl_Position = u_MVP * a_Position;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 o_FragColour;

//Vector
in vec4 v_Colour;
in vec2 v_TexCoord;
in float v_TexID;

//Ambient Light
uniform float u_ambientLightStrenght;
uniform vec3 u_ambientLightColour;

//Texture
uniform sampler2D u_Textures[2];

void main()
{
    //Unlit
    int index = int(v_TexID);
    vec4 unlitResult = texture(u_Textures[index], v_TexCoord) * v_Colour;

    //Ambient Lighting
    vec3 ambientLight = u_ambientLightStrenght * u_ambientLightColour;
    vec4 ambientResult = unlitResult * vec4(ambientLight, 1.0);

    o_FragColour = ambientResult;
}