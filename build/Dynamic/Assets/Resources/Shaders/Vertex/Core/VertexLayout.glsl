layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec4 a_Colour;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in float a_TexID;
//layout 5, 6, 7 and 8 is given to instancing
#ifdef INSTANCING
    layout(location = 9) in float a_InstanceTexID;
    float GetTextureID()
    {
        return a_InstanceTexID;
    }

    layout(location = 10) in vec2 a_UVMin;
    layout(location = 11) in vec2 a_UVMax;
    vec2 GetTextureCoordinate()
    {
        return mix(a_UVMin, a_UVMax, a_TexCoord);
    }

#else
    float GetTextureID()
    {
        return a_TexID;
    }

    vec2 GetTextureCoordinate()
    {
        return a_TexCoord;
    }
#endif

out vec4 v_Pos;
out vec3 v_Normal;
out vec4 v_Colour;
out vec2 v_TexCoord;
flat out float v_TexID;