
float SphericalWarpAxis(float coordinate)
{
    return sin(coordinate * u_WarpStrength) * u_WarpScale;
}