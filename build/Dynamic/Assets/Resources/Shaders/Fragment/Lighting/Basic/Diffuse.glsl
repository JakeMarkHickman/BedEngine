uniform vec3 u_DiffuseLightPos;
uniform vec3 u_DiffuseLightColour;

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