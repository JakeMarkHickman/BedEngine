#shader vertex
#version 450 core

#define INSTANCING

#include "Vertex/Core/VertexLayout.glsl"
#include "Vertex/Core/ModelViewProjection.glsl"

void main()
{
    v_Colour = a_Colour;
    v_TexCoord = a_TexCoord;
    v_TexID = GetTextureID();
    gl_Position = Transform(a_Position);
}


#shader fragment
#version 450 core

#include "Fragment/Core/VertexLayout.glsl"
#include "Fragment/Core/FragColour.glsl"

#include "Fragment/Material/Texture.glsl"

void main()
{
    vec3 result = ApplyTexture(int(v_TexID), v_TexCoord, v_Colour);

    //Output
    o_FragColour = vec4(result, 1.0);
}