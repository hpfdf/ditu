#ifndef _JSONOBJECT_H_
#define _JSONOBJECT_H_

#include <vector>
#include <string>

#include "libJson/json.h"

// The abstract base class for all serializable data structure.
//
// Subclasses are expected to contain new members or methods, but
// they must implement FromJson() and ToJson(). Once the two virtual
// methods are correctly overloaded, the public methods (saves and loads)
// should be ready.
class JsonObject {
  public:
    // Deserialize
    bool FromString(const char *s);

    // Serialize
    std::string ToString();

    // Save to file
    bool Save(const char *dir);

    // Load from file
    bool Load(const char *dir);

    // Convert a JsonObject or a Basic type variable to Json value.
    template <typename T>
    friend Json::Value ConvertToJson(T t);

    // Parse a Json value into correct type and return true when success.
    template <typename T>
    friend bool ConvertFromJson(const Json::Value &v, T *t);

  protected:
    // Construct from a Json value
    virtual bool FromJson(const Json::Value &v);

    // Store in a Json value
    virtual Json::Value ToJson() const;
};

// List template of JsonObject.
template <typename T>
class JsonObjectList : public JsonObject {
  public:
    // List related methods
    int size() const {
        return static_cast<int>(array.size());
    }
    const T &operator[] (int index) const {
        return array[index];
    }
    T &operator[] (int index) {
        return array[index];
    }
    typename std::vector<T>::const_iterator begin() const {
        return array.begin();
    }
    typename std::vector<T>::const_iterator end() const {
        return array.end();
    }
    typename std::vector<T>::iterator begin() {
        return array.begin();
    }
    typename std::vector<T>::iterator end() {
        return array.end();
    }
    void append(const T &t) {
        array.push_back(t);
    }
    void resize(int size) {
        array.resize(size);
    }

    // Refer
    const std::vector<T> &AsVector() const {
        return array;
    }
    typename std::vector<T> &AsVector() {
        return array;
    }
    const T *AsArray() const {
        return array.const_data();
    }
    T *AsArray() {
        return array.data();
    }

  protected:
    typename std::vector<T> array;
    virtual bool FromJson(const Json::Value &v) {
        if (!v.isArray()) {
            return false;
        }
        array.clear();
        for (auto i : v) {
            T t;
            if (!ConvertFromJson(i, &t)) {
                return false;
            }
            array.push_back(t);
        }
        return true;
    }
    virtual Json::Value ToJson() const {
        Json::Value v;
        v.resize(size());
        int i = 0;
        for (const auto &k : array) {
            v[i++] = ConvertToJson(k);
        }
        return v;
    }
};

// Basic type (int, float, string) wrapping for Json IO
template <>
Json::Value ConvertToJson(int t) {
    return Json::Value(t);
}

template <>
Json::Value ConvertToJson(float t) {
    return Json::Value(t);
}

template <>
Json::Value ConvertToJson(const std::string &t) {
    return Json::Value(t);
}

template <>
Json::Value ConvertToJson(const JsonObject& t) {
    return t.ToJson();
}

template <>
bool ConvertFromJson(const Json::Value &v, int *t) {
    if (!v.isInt()) {
        return false;
    }
    *t = v.asInt();
    return true;
}

template <>
bool ConvertFromJson(const Json::Value &v, float *t) {
    if (!v.isNumeric()) {
        return false;
    }
    *t = v.asFloat();
    return true;
}

template <>
bool ConvertFromJson(const Json::Value &v, std::string *t) {
    if (!v.isString()) {
        return false;
    }
    *t = v.asString();
    return true;
}

template <>
bool ConvertFromJson(const Json::Value &v, JsonObject *t) {
    return t->FromJson(v);
}

#endif

