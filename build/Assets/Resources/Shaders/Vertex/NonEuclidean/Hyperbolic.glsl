
float HyperbolicWarpAxis(float coordinate)
{
    return tanh(coordinate * u_WarpStrength) * u_WarpScale;
}

float tanh(float x)
{
    float cal1 = exp(x);
    float cal2 = exp(-x);

    return (cal1 - cal2) / (cal1 + cal2);
}
