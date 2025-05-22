
uniform mat4 u_View;
uniform mat4 u_Projection;

#ifdef INSTANCING
    layout(location = 5)in mat4 a_Model;
    mat4 GetModelMatrix()
    {
        return a_Model;
    }
#else
    uniform mat4 u_Model;
    mat4 GetModelMatrix()
    {
        return u_Model;
    }
#endif

vec4 ModelTransform(vec4 pos)
{
    return GetModelMatrix() * pos;
}

vec4 Transform(vec4 pos)
{
    return u_Projection * u_View * ModelTransform(pos);
}