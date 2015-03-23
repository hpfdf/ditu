#ifndef _JSONOBJECT_H_
#define _JSONOBJECT_H_

#include <cstring>
#include <string>
#include <vector>

#include "libJson/json.h"

// The abstract base class for all serializable data structure.
// Subclasses are expected to contain new members or methods, but
// they must implement FromJson() and ToJson()
class JsonObject {
  public:
    // Deserialize
    bool FromString(const char *s) {
        Json::Reader r;
        Json::Value v;
        if (!r.parse(s, s + std::strlen(s), v, false)) {
            return false;
        }
        return FromJson(v);
    }

    // Serialize
    std::string ToString() {
        return ToJson().toStyledString();
    }

  protected:
    // Construct from a Json value
    virtual bool FromJson(const Json::Value &v) = 0;
    virtual Json::Value ToJson() const = 0;
};


#endif

