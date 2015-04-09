#ifndef _CONTENTS_H_
#define _CONTENTS_H_

#include "../utils/jsonobject.h"

// Identify a position in the map (in meters).
class Point : public JsonObject {
  public:
    float x;
    float y;

    JSON_MEMBERS(x, y)
};

// Identify a segment.
class Segment : public JsonObject {
  public:
    Point p1;
    Point p2;

    JSON_MEMBERS(p1, p2)
};

// Identify a position with height in the map.
class Point3D : public JsonObject {
  public:
    float x;
    float y;
    float z;

    JSON_MEMBERS(x, y, z)

    Point GetPoint() const;
};

// Identify a polygon in the map, where type can be
// "wall"       : Cannot pass in any height.
// "up"         : Stairs going up.
// "down"       : Stairs going down.
// "range"      : Target can only be in range. There is only one range in a floor.
// "barrier"    : Target cannot pass, but the space is connected in some height.
// "region"     : Searchable comment region.
// "decoration" : Unsearchable comment region.
// "label"      : Map positioning data region.
class Polygon : public JsonObject {
  public:
    std::string type;
    JsonObjectList<Point> shape;

    JSON_MEMBERS(type, shape)
};

// 2D Geometry algorithm utilities.
class GeometryUtils {
  public:
    // Whether segment a-b intersects with segment c-d.
    static bool Cut(const Point &a, const Point &b, const Point &c, const Point &d);

    // Whether point p is inside polygon a.
    static bool Inside(const Point &p, const Polygon &a);

    // Whether polygon a hits polygon b.
    static bool Hit(const Polygon &a, const Polygon &b);

    // Return the length of a route
    static float Length(const JsonObjectList<Point> &route);
};

// Identify a text label in the map in a polygon.
class Comment : public JsonObject {
  public:
    std::string text;
    Polygon polygon;

    JSON_MEMBERS(text, polygon)
};

// Identify a observation from IMU or FingerPrint sensors.
// e.g.,
// 1. type="wifi", sub="87:65:43:21:0f:ed", data=(wifi signal intensity)
// TODO(Qiwei): Define IMU observations.
class Observe : public JsonObject {
  public:
    int time;
    std::string type;
    std::string sub;
    float data;

    JSON_MEMBERS(time, type, sub, data)
};

// Identify a data label in the map for locating.
// e.g.,
// 1. type="wifi", sub="87:65:43:21:0f:ed", data=(wifi signal intensity)
class Label : public JsonObject {
  public:
    Point pos;
    std::string type;
    std::string sub;
    float data;

    JSON_MEMBERS(pos, type, sub, data)
};

// Identify a composite floor map with all geometrics, labels and comments.
class Floor : public JsonObject {
  public:
    JsonObjectList<Polygon> objects;
    JsonObjectList<Comment> comments;
    JsonObjectList<Label> labels;

    JSON_MEMBERS(objects, comments, labels)
};

#endif
