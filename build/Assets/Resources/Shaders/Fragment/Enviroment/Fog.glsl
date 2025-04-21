uniform bool u_EnableFog;

uniform vec3 u_FogColour;
uniform float u_FogNear;
uniform float u_FogFar;

vec3 CalculateFog(vec3 sceneColour, float distanceToCamera)
{
    float fogFactor = clamp((u_FogFar - distanceToCamera) / (u_FogFar - u_FogNear), 0.0, 1.0);
    return mix(u_FogColour, sceneColour, fogFactor);
}