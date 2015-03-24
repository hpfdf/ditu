#include "contents.h"

Point Point3D::GetPoint() const {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

bool GeometryUtils::Cut(const Point &a, const Point &b, const Point &c, const Point &d) {
    // TODO
    return false;
}

bool GeometryUtils::Inside(const Point &p, const Polygon &a) {
    // TODO
    return false;
}

bool GeometryUtils::Hit(const Polygon &a, const Polygon &b) {
    // TODO
    return false;
}

float GeometryUtils::Length(const JsonObjectList<Point> &route) {
    // TODO
    return 0;
}

