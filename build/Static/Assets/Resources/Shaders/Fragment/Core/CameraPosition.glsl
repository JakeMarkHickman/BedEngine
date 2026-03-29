in vec3 v_CamPos;

float CalculateDistanceFromCamera(vec3 Pos)
{
    return length(Pos - v_CamPos);
}