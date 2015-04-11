#include "mapcamera.h"

#include <complex>

void MapCamera::ScreenToReal(float cx, float cy, float *rx, float *ry)
{
    std::complex<float> p(cx, cy);
    p *= std::polar(scale, angle);
    *rx = p.real() + x;
    *ry = p.imag() + y;
}

void MapCamera::RealToScreen(float rx, float ry, float *cx, float *cy)
{
    std::complex<float> p(rx - x, ry - y);
    p /= std::polar(scale, angle);
    *cx = p.real();
    *cy = p.imag();
}

void MapCamera::move(float dx, float dy)
{
    x += dx;
    y += dy;
}

void MapCamera::rotate(float a, float sx, float sy)
{
    angle += a;
    float dx, dy;
    RealToScreen(x, y, &dx, &dy);
    std::complex<float> p(dx - sx, dy - sy);
    p *= std::polar(1.f, a);
    dx = p.real() + sx;
    dy = p.imag() + sy;
    ScreenToReal(dx, dy, &x, &y);
}

MapCamera::MapCamera() : x(0), y(0), scale(1), angle(0)
{
}

MapCamera::~MapCamera()
{

}

