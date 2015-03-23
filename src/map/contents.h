#ifndef _CONTENTS_H_
#define _CONTENTS_H_

#include "jsonobject.h"

class Point : public JsonObject {
  public:
    float x;
    float y;

    virtual bool FromJson(const Json::Value &v) {
        if (v["x"].isFloat() && v["y"].isFloat()) {
            x = v["x"].asFloat();
            y = v["y"].asFloat();
            return true;
        } else {
            return false;
        }
    }
    virtual Json::Value ToJson() const {
        Json::Value v;
        v["x"] = Json::Value(x);
        v["y"] = Json::Value(y);
        return v;
    }
};

class PointList : public JsonObject {
  public:
    std::vector<Point> p;

    int size() {
        return p.size();
    }

    Point &operator[] (int index) {
        auto l = p.size();
        return p[(index % l + l) % l];
    }

    std::vector<Point>::const_iterator begin() const {
        return p.begin();
    }

    std::vector<Point>::const_iterator end() const {
        return p.end();
    }

    std::vector<Point>::iterator begin() {
        return p.begin();
    }

    std::vector<Point>::iterator end() {
        return p.end();
    }

  protected:
    virtual bool FromJson(const Json::Value &v) {
        p.clear();
        if (v.isArray()) {
            for (auto i : v) {
                Point t;
                if (!t.FromJson(i)) {
                    return false;
                }
                p.push_back(t);
            }
            return true;
        } else {
            return false;
        }
    }

    virtual Json::Value ToJson() const {
        Json::Value v;
        v.resize(p.size());
        int k = 0;
        for (const auto &i : p) {
            v[k++] = i.ToJson();
        }
        return v;
    }
};

class Polygon : public JsonObject {
  public:
    std::string type;
    PointList pts;

    virtual bool FromJson(const Json::Value &v) {
        if (v["type"].isString() && pts.FromJson(v["shape"])) {
            type = v["type"].asString();
            return true;
        } else {
            return false;
        }
    }

    virtual Json::Value ToJson() const {
        Json::Value v;
        v["type"] = Json::Value(type);
        v["shape"] = pts.ToJson();
        return v;
    }
};

class GeometryUtils {
  public:
    // Whether segment a-b intersects with segment c-d.
    static bool Cut(const Point &a, const Point &b, const Point &c, const Point &d) {
        // TODO
        return false;
    }

    // Whether point p is inside polygon a.
    static bool Inside(const Point &p, const Polygon &a) {
        // TODO
        return false;
    }

    // Whether polygon a hits polygon b.
    static bool Hit(const Polygon &a, const Polygon &b) {
        // TODO
        return false;
    }
};

class Comment : public JsonObject {
  public:
    std::string text;
    PointList pts;
    
    virtual bool FromJson(const Json::Value &v) {
        if (v["text"].isString() && pts.FromJson(v["shape"])) {
            type = v["text"].asString();
            return true;
        } else {
            return false;
        }
    }

    virtual Json::Value ToJson() const {
        Json::Value v;
        v["text"] = Json::Value(type);
        v["shape"] = pts.ToJson();
        return v;
    }
}

class Observe : public JsonObject {
  public:
    uint64_t time;
    std::string type;
    std::string sub;
    float data;

    virtual bool FromJson(const Json::Value &v) {
        if (v["x"].isFloat() && v["y"].isFloat() && v["data"].isFloat() &&
            v["type"].isString() && v["sub"].isString()) {
            x = v["x"].asFloat();
            y = v["y"].asFloat();
            sub = v["sub"].asString();
            type = v["type"].asString();
            data = v["data"].asFloat();
            return true;
        } else {
            return false;
        }
    }

    virtual Json::Value ToJson() const {
        Json::Value v;
        v["x"] = Json::Value(x);
        v["y"] = Json::Value(y);
        v["type"] = Json::Value(type);
        v["sub"] = Json::Value(sub);
        v["data"] = Json::Value(data);
        return v;
    }
};

class Label : public JsonObject {
  public:
    Point p;
    std::string type;
    std::string sub;
    float data;

    virtual bool FromJson(const Json::Value &v) {
        if (v["x"].isFloat() && v["y"].isFloat() && v["data"].isFloat() &&
            v["type"].isString() && v["sub"].isString()) {
            x = v["x"].asFloat();
            y = v["y"].asFloat();
            sub = v["sub"].asString();
            type = v["type"].asString();
            data = v["data"].asFloat();
            return true;
        } else {
            return false;
        }
    }

    virtual Json::Value ToJson() const {
        Json::Value v;
        v["x"] = Json::Value(x);
        v["y"] = Json::Value(y);
        v["type"] = Json::Value(type);
        v["sub"] = Json::Value(sub);
        v["data"] = Json::Value(data);
        return v;
    }
};

class Floor : public JsonObject {
  public:
    std::vector<Polygon> objects;
    std::vector<Comment> comments;
    std::vector<Label> labels;

    virtual bool FromJson(const Json::Value &v) {
        if (v["objects"].isArray() && v["comments"].isArray() &&
            v["labels"].isArray()) {
            objects.clear();
            for (auto i : v["objects"]) {
                Polygon p;
                if (!p.FromJson(i)) {
                    return false;
                }
                objects.push_back(p);
            }
            comments.clear();
            for (auto i : v["comments"]) {
                Comment p;
                if (!p.FromJson(i)) {
                    return false;
                }
                comments.push_back(p);
            }
            labels.clear();
            for (auto i : v["labels"]) {
                Label p;
                if (!p.FromJson(i)) {
                    return false;
                }
                labels.push_back(p);
            }
            return true;
        } else {
            return false;
        }
    }

    virtual Json::Value ToJson() const {
        Json::Value v;
        int k;
        v["objects"].resize(objects.size());
        k = 0;
        for (const auto &i : objects) {
            v["objects"][k++] = i.ToJson();
        }
        v["comments"].resize(comments.size());
        k = 0;
        for (const auto &i : comments) {
            v["comments"][k++] = i.ToJson();
        }
        v["labels"].resize(labels.size());
        k = 0;
        for (const auto &i : labels) {
            v["labels"][k++] = i.ToJson();
        }
        return v;
    }
};

#endif
