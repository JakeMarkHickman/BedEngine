layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec4 a_Colour;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in float a_TexID;

out vec4 v_Pos;
out vec3 v_Normal;
out vec4 v_Colour;
out vec2 v_TexCoord;
flat out float v_TexID;