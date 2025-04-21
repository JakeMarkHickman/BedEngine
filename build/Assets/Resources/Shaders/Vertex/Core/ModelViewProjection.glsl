uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

vec4 ModelTransform(vec4 pos)
{
    return u_Model * pos;
}

vec4 Transform(vec4 pos)
{
    return u_Projection * u_View * ModelTransform(pos);
}