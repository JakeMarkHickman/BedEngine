#shader vertex
#version 450 core

#define INSTANCING

#include "Vertex/Core/VertexLayout.glsl"
#include "Vertex/Core/ModelViewProjection.glsl"

void main()
{
    v_Pos = ModelTransform(a_Position);
    v_Normal = a_Normal;
    v_Colour = a_Colour;
    v_TexCoord = GetTextureCoordinate();
    v_TexID = GetTextureID();

    gl_Position = Transform(a_Position);
}


#shader fragment
#version 450 core

#include "Fragment/Core/VertexLayout.glsl"
#include "Fragment/Core/FragColour.glsl"

#include "Fragment/Material/Material.glsl"

#include "Fragment/lighting/PhongLighting.glsl"

void main()
{
    //Unlit
    vec3 unlitResult = ApplyTexture(int(v_TexID), v_TexCoord, v_Colour);

    //Light Direction
    vec3 lightDir = normalize(u_DiffuseLightPos - v_Pos.xyz);

    //Final Colour Calculation
    vec3 result = (CalculateAmbientLight() + CalculateDiffuse(u_DiffuseLightColour, lightDir)) * unlitResult;

    //Output
    o_FragColour = vec4(result, 1.0);
}