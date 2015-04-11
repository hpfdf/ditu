#ifndef MAPCAMERA_H
#define MAPCAMERA_H

class MapCamera
{
public:
    float x, y, scale, angle;

    void ScreenToReal(float sx, float sy, float *rx, float *ry);
    void RealToScreen(float rx, float ry, float *sx, float *sy);
    void move(float dx, float dy);
    void rotate(float a, float sx = 0, float sy = 0);

    MapCamera();
    ~MapCamera();
};

#endif // MAPCAMERA_H
