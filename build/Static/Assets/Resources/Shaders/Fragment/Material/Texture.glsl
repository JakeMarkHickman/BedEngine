uniform sampler2D u_Textures[32];

vec3 ApplyTexture(int index, vec2 textureCoord, vec4 colour)
{
    return vec3(texture(u_Textures[index], textureCoord) * colour);
}