
//TODO: currently doesn't have any different functionality from Spherical

float EllipticWarpAxis(float coordinate)
{
    float safe = clamp(coordinate, -1.55 / u_WarpStrength, 1.55 / u_WarpStrength);
    float warped = tan(safe * u_WarpStrength) * u_WarpScale;

    return warped;
}