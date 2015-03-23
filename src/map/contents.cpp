#include "contents.h"

bool Point::FromJson(const Json::Value &v) {
    return ConvertFromJson(v["x"], &x) && ConvertFromJson(v["y"], &y);
}

Json::Value Point::ToJson() const {
    Json::Value v;
    v["x"] = ConvertToJson(x);
    v["y"] = ConvertToJson(y);
    return v;
}

bool Point3D::FromJson(const Json::Value &v) {
    return ConvertFromJson(v["x"], &x) && ConvertFromJson(v["y"], &y) &&
        ConvertFromJson(v["z"], &z);
}

Json::Value Point3D::ToJson() const {
    Json::Value v;
    v["x"] = ConvertToJson(x);
    v["y"] = ConvertToJson(y);
    v["z"] = ConvertToJson(z);
    return v;
}

Point Point3D::GetPoint() const {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

bool Polygon::FromJson(const Json::Value &v) {
    return ConvertFromJson(v["type"], &type) && ConvertFromJson(v["shape"], &points);
}

Json::Value Polygon::ToJson() const {
    Json::Value v;
    v["type"] = ConvertToJson(type);
    v["shape"] = ConvertToJson(points);
    return v;
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

float GeometryUtils::Length(const JsonObjectList<Point> &route)
    // TODO
    return 0;
}

bool Comment::FromJson(const Json::Value &v) {
    return ConvertFromJson(v["text"], &text) && ConvertFromJson(v["region"], &region);
}

Json::Value Comment::ToJson() const {
    Json::Value v;
    v["text"] = ConvertToJson(text);
    v["region"] = ConvertToJson(region);
    return v;
}

bool Observe::FromJson(const Json::Value &v) {
    return ConvertFromJson(v["time"], &time) && ConvertFromJson(v["type"], &type) &&
        ConvertFromJson(v["sub"], &sub) && ConvertFromJson(v["data"], &data);
}

Json::Value Observe::ToJson() const {
    Json::Value v;
    v["time"] = ConvertToJson(time);
    v["type"] = ConvertToJson(type);
    v["sub"] = ConvertToJson(sub);
    v["data"] = ConvertToJson(data);
    return v;
}

bool Label::FromJson(const Json::Value &v) {
    return ConvertFromJson(v["pos"], &pos) && ConvertFromJson(v["type"], &type) &&
        ConvertFromJson(v["sub"], &sub) && ConvertFromJson(v["data"], &data);
}
    
Json::Value Label::ToJson() const {
    Json::Value v;
    v["pos"] = ConvertToJson(pos);
    v["type"] = ConvertToJson(type);
    v["sub"] = ConvertToJson(sub);
    v["data"] = ConvertToJson(data);
    return v;
}

bool Floor::FromJson(const Json::Value &v) {
    return ConvertFromJson(v["objects"], &objects) &&
        ConvertFromJson(v["comments"], &comments) &&
        ConvertFromJson(v["labels"], &labels);
}

Json::Value Floor::ToJson() const {
    Json::Value v;
    v["objects"] = ConvertToJson(objects);
    v["comments"] = ConvertToJson(comments);
    v["labels"] = ConvertToJson(labels);
    return v;
}

