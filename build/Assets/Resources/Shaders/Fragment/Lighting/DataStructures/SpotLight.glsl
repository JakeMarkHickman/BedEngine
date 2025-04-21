struct SpotLight
{
    vec3 Position;
    float Padding1;
    vec3 Colour;
    float Padding2;
    vec3 Direction;
    float Padding3;
    float Strength;
    float CutOff;
    float OuterCutOff;
    float Radius;
    float padding4[4];
};

layout(std430, binding = 1) buffer SpotLightBuffer{
    SpotLight spotLights[];
};