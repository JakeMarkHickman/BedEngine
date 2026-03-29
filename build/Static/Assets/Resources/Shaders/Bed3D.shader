#shader vertex
#version 450 core

#include "Vertex/Core/VertexLayout.glsl"
#include "Vertex/Core/ModelViewProjection.glsl"
#include "Vertex/Core/CameraPosition.glsl"
#include "Vertex/NonEuclidean/NonEuclidean.glsl"

void main()
{
    vec4 WorldPos = ModelTransform(a_Position);

    vec3 localToCamera = WorldPos.xyz - u_CamPos;

    //localToCamera.x = HyperbolicWarpAxis(localToCamera.x);
    //localToCamera.y = HyperbolicWarpAxis(localToCamera.y);
    //localToCamera.z = HyperbolicWarpAxis(localToCamera.z);

    //localToCamera.x = SphericalWarpAxis(localToCamera.x);
    //localToCamera.y = SphericalWarpAxis(localToCamera.y);
    //localToCamera.z = SphericalWarpAxis(localToCamera.z);

    //localToCamera.x = EllipticWarpAxis(localToCamera.x);
    //localToCamera.y = EllipticWarpAxis(localToCamera.y);
    //localToCamera.z = EllipticWarpAxis(localToCamera.z);

    WorldPos.xyz = u_CamPos + localToCamera; 

    v_Pos = WorldPos;
    v_Normal = normalize(a_Normal);
    v_Colour = a_Colour;
    v_TexCoord = a_TexCoord;
    v_TexID = a_TexID;
    v_CamPos = u_CamPos;

    gl_Position = Transform(WorldPos);
}

#shader fragment
#version 450 core

#include "Fragment/Core/VertexLayout.glsl"
#include "Fragment/Core/CameraPosition.glsl"
#include "Fragment/Core/FragColour.glsl"

#include "Fragment/Material/Material.glsl"

#include "Fragment/Lighting/PhongLighting.glsl"

#include "Fragment/Enviroment/Fog.glsl"

void main()
{
    bool unlit = u_GlobalUnlit || u_MaterialUnlit;

    vec3 result = ApplyTexture(int(v_TexID), v_TexCoord, v_Colour);

    if(!unlit)
    {
        //PointLight
        vec3 point = vec3(0.0);

        for(int i = 0; i < 10; i++)//TODO: this needs to be dynamic
        {
            vec3 pointResult = CalculatePointLight(pointLights[i], v_CamPos);
            point += pointResult;
        }

        //SpotLight
        vec3 spot = vec3(0.0);

        for(int i = 0; i < 10; i++)//TODO: this needs to be dynamic
        {
            vec3 spotResult = CalculateSpotLight(spotLights[i], v_CamPos);
            spot += spotResult;
        }

        //DirectionalLight
        vec3 directional = vec3(0.0);
        
        for(int i = 0; i < 10; i++)//TODO: this needs to be dynamic
        {
            vec3 dirResult = CalculateDirectionalLight(directionalLights[i], v_CamPos);
            directional += dirResult;
        }

        //Final Colour Calculation
        result = (CalculateAmbientLight() + point + spot + directional) * result;
    }

    if(!unlit && u_EnableFog)
    {
        result = CalculateFog(result, CalculateDistanceFromCamera(v_Pos.xyz));
    }
    
    //Output
    o_FragColour = vec4(result, 1.0);//vec4(vec3(v_TexID / 31.0), 1.0);
}