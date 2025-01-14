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
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_CamPos;

out vec4 v_Pos;
out vec3 v_Normal;
out vec4 v_Colour;
out vec2 v_TexCoord;
out float v_TexID;
out vec3 v_CamPos;

void main()
{
    v_Pos = u_Model * a_Position;
    v_Normal = normalize(a_Normal);
    v_Colour = a_Colour;
    v_TexCoord = a_TexCoord;
    v_TexID = a_TexID;
    v_CamPos = u_CamPos;
    gl_Position = u_Projection * u_View * u_Model * a_Position;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 o_FragColour;

// Vector
in vec4 v_Pos;
in vec3 v_Normal;
in vec4 v_Colour;
in vec2 v_TexCoord;
in float v_TexID;

// Camera
in vec3 v_CamPos;

// Point Light
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

// Spot Light
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

// Directional Light
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

//Ambient Light
uniform float u_ambientLightStrength;
uniform vec3 u_ambientLightColour;

//Diffuse Light
uniform vec3 u_DiffuseLightPos;
uniform vec3 u_DiffuseLightColour;

//Texture
uniform sampler2D u_Textures[2];

vec3 CalculateDiffuse(vec3 lightColour, vec3 lightDir)
{
    float diff = max(dot(v_Normal, lightDir), 0.0);
    return diff * lightColour;
}

vec3 CalculateSpecular(vec3 lightColour, vec3 lightDir, vec3 viewPos)
{
    vec3 reflectDir = reflect(-lightDir, v_Normal);
    vec3 viewDir = normalize(viewPos - v_Pos.xyz);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    return spec * lightColour;
}

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

void main()
{
    //Unlit
    int index = int(v_TexID);
    vec3 unlitResult = vec3(texture(u_Textures[index], v_TexCoord) * v_Colour);

    //Ambient Lighting
    vec3 ambientLight = u_ambientLightStrength * u_ambientLightColour;

    //PointLight
    vec3 point;

    for(int i = 0; i < 10; i++)//TODO: this needs to be dynamic
    {
        vec3 pointResult = CalculatePointLight(pointLights[i], v_CamPos);
        point += pointResult;
    }

    //SpotLight
    vec3 spot;

    for(int i = 0; i < 10; i++)//TODO: this needs to be dynamic
    {
        vec3 spotResult = CalculateSpotLight(spotLights[i], v_CamPos);
        spot += spotResult;
    }

    //DirectionalLight
    vec3 directional;
    
    for(int i = 0; i < 10; i++)//TODO: this needs to be dynamic
    {
        vec3 dirResult = CalculateDirectionalLight(directionalLights[i], v_CamPos);
        directional += dirResult;
    }

    //Final Colour Calculation
    vec3 result = (ambientLight + point + spot + directional) * unlitResult;

    //Output
    o_FragColour = vec4(result, 1.0);
}