struct DirectionalLight
{
    vec3 Colour;
    float Padding1;
    vec3 Direction;
    float Padding2;
    float Strength;
    float Padding3;
};

layout(std430, binding = 2) buffer DirectionalLightBuffer{
    DirectionalLight directionalLights[];
};