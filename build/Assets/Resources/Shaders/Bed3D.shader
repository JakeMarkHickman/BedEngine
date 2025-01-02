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
uniform mat4 u_ViewProjection;

out vec4 v_Pos;
out vec3 v_Normal;
out vec4 v_Colour;
out vec2 v_TexCoord;
out float v_TexID;

void main()
{
    v_Pos = u_Model * a_Position;
    v_Normal = a_Normal;
    v_Colour = a_Colour;
    v_TexCoord = a_TexCoord;
    v_TexID = a_TexID;
    gl_Position = u_ViewProjection * u_Model * a_Position;
}


#shader fragment
#version 450 core

layout(location = 0) out vec4 o_FragColour;

//Vector
in vec4 v_Pos;
in vec3 v_Normal;
in vec4 v_Colour;
in vec2 v_TexCoord;
in float v_TexID;

//Ambient Light
uniform float u_ambientLightStrenght;
uniform vec3 u_ambientLightColour;

//Diffuse Light
uniform vec3 u_DiffuseLightPos;
uniform vec3 u_DiffuseLightColour;

//Texture
uniform sampler2D u_Textures[2];

vec3 CalculateDiffuse(vec3 baseColour, vec3 norm, vec3 lightDir)
{
    float diff = max(dot(norm, lightDir), 0.0);
    return diff * baseColour;
}

vec3 CalculateSpecular(vec3 lightColour, float lightStrenght, vec3 norm, vec3 lightDir, vec3 viewPos)
{
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(viewPos - vec3(v_Pos));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    return spec * lightColour * lightStrenght;
}

void main()
{
    //Unlit
    int index = int(v_TexID);
    vec3 unlitResult = vec3(texture(u_Textures[index], v_TexCoord) * v_Colour);

    //Ambient Lighting
    vec3 ambientLight = u_ambientLightStrenght * u_ambientLightColour;

    //Diffuse Lighting
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_DiffuseLightPos - v_Pos.xyz);
    vec3 diffuse = CalculateDiffuse(u_DiffuseLightColour, norm, lightDir);
    vec3 specular = CalculateSpecular(vec3(1.0, 1.0, 1.0), 1.0, norm, lightDir, vec3(1.0, 1.0, 1.0));

    //Final Colour Calculation
    vec3 result = (ambientLight + diffuse + specular) * unlitResult;

    //Output
    o_FragColour = vec4(result, 1.0);
}