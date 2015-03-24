#ifndef _JSONOBJECT_H_
#define _JSONOBJECT_H_

#include <vector>
#include <string>
#include <cstdio>

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
    friend inline Json::Value ConvertToJson(T t);

    // Parse a Json value into correct type and return true when success.
    template <typename T>
    friend inline bool ConvertFromJson(const Json::Value &v, T *t);

  protected:
    // Construct from a Json value
    virtual bool FromJson(const Json::Value &v);

    // Store in a Json value
    virtual Json::Value ToJson() const;

// =============================
// for simplification JSON_MEMBERS macro, never use.
    void __f() {}
    template<typename T, typename... S>
    void __f(T& __t, S&... __s) {
        __ret &= ConvertFromJson(__v[__members[__i++]], &__t);
        __f(__s...);
    }
    void __g() const {}
    template<typename T, typename... S>
    void __g(T& __t, S&... __s) const {
        __v[__members[__i++]] = ConvertToJson(__t);
        __g(__s...);
    }
#define JSON_MEMBERS(args...) \
    virtual bool FromJson(const Json::Value &__vv) { \
        __v = __vv; \
        __ret = true; \
        __members = SplitIdentifiers(#args); \
        __i = 0; \
        __f(args);    \
        return __ret; \
    } \
    virtual Json::Value ToJson() const { \
        __v = Json::Value(); \
        __members = SplitIdentifiers(#args); \
        __i = 0; \
        __g(args); \
        return __v; \
    } \

    mutable bool __ret;
    mutable Json::Value __v;
    mutable std::vector<std::string> __members;
    mutable int __i;
// =============================
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

// Split identifier list to string array.
// E.g., "a,b,c" -> {"a", "b", "c"}
inline std::vector<std::string> SplitIdentifiers(const char *s) {
    std::vector<std::string> ret;
    std::string r = "";
    for (const char *p = s; *p; ++p) {
        if (*p == '(') {
            r = "";
        } else if (*p == ')' || *p == ',') {
            ret.push_back(r);
            r = "";
        } else if (!isblank(*p)) {
            r += *p;
        }
    }
    ret.push_back(r);
    return ret;
}

// Basic type (int, float, string) wrapping for Json IO
template <>
inline Json::Value ConvertToJson(int t) {
    return Json::Value(t);
}

template <>
inline Json::Value ConvertToJson(float t) {
    return Json::Value(t);
}

template <>
inline Json::Value ConvertToJson(double t) {
    return Json::Value(t);
}

template <>
inline Json::Value ConvertToJson(std::string t) {
    return Json::Value(t);
}

template <>
inline bool ConvertFromJson(const Json::Value &v, int *t) {
    if (!v.isInt()) {
        return false;
    }
    *t = v.asInt();
    return true;
}

template <>
inline bool ConvertFromJson(const Json::Value &v, float *t) {
    if (!v.isNumeric()) {
        return false;
    }
    *t = v.asFloat();
    return true;
}

template <>
inline bool ConvertFromJson(const Json::Value &v, double *t) {
    if (!v.isNumeric()) {
        return false;
    }
    *t = v.asDouble();
    return true;
}

template <>
inline bool ConvertFromJson(const Json::Value &v, std::string *t) {
    if (!v.isString()) {
        return false;
    }
    *t = v.asString();
    return true;
}

template <typename T>
inline Json::Value ConvertToJson(T t) {
    auto p = dynamic_cast<JsonObject*>(&t);
    if (p == nullptr) {
        return Json::Value();
    } else {
        return p->ToJson();
    }
}

template <typename T>
inline bool ConvertFromJson(const Json::Value &v, T *t) {
    auto p = dynamic_cast<JsonObject*>(t);
    if (p == nullptr) {
        return false;
    } else {
        return p->FromJson(v);
    }
}

#endif
