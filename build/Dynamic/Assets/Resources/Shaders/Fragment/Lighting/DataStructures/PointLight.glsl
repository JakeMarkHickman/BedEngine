struct PointLight
{
    vec3 Position;
    float Padding1;
    vec3 Colour;
    float Padding2;
    float Strength;
    float Radius;
    float padding3[2];
};

layout(std430, binding = 0) buffer PointLightBuffer {
    PointLight pointLights[];
};