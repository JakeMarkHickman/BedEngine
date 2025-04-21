#include "DataStructures/AmbientLight.glsl"
#include "DataStructures/PointLight.glsl"
#include "DataStructures/DirectionalLight.glsl"
#include "DataStructures/SpotLight.glsl"

#include "Basic/Diffuse.glsl"

vec3 CalculatePointLight(PointLight light, vec3 viewPos)
{
    vec3 lightDir = normalize(light.Position - v_Pos.xyz);
    float distance = length(light.Position - v_Pos.xyz);
    float attenuation = 1.0 / (distance / light.Radius + 1.0); // TODO: Example attenuation calculate proper fall off

    vec3 diffuse = CalculateDiffuse(light.Colour, lightDir) * attenuation;
    vec3 specular = CalculateSpecular(light.Colour, lightDir, viewPos) * attenuation;

    return diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 viewPos)
{
    vec3 lightDir = normalize(light.Position - v_Pos.xyz);
    float theta = dot(lightDir, normalize(-light.Direction));

    float epsilon = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);

    float distance = length(light.Position - v_Pos.xyz);
    float attenuation = 1.0 / (distance / light.Radius + 1.0); // TODO: Example attenuation calculate proper fall off
    
    vec3 diffuse = CalculateDiffuse(light.Colour, lightDir) * attenuation * intensity;
    vec3 specular = CalculateSpecular(light.Colour, lightDir, viewPos) * attenuation * intensity;

    return diffuse + specular;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 viewPos)
{
    vec3 lightDir = normalize(-light.Direction);

    vec3 diffuse = CalculateDiffuse(light.Colour, lightDir) * light.Strength;
    vec3 specular = CalculateSpecular(light.Colour, lightDir, viewPos) * light.Strength;

    return diffuse + specular;
}

vec3 CalculateAmbientLight()
{
    return u_ambientLightStrength * u_ambientLightColour;
}