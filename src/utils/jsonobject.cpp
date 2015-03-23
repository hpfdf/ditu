#include "jsonobject.h"

#include <cstring>

#include "libJson/json.h"

bool JsonObject::FromString(const char *s) {
    Json::Reader r;
    Json::Value v;
    if (!r.parse(s, s + std::strlen(s), v, false)) {
        return false;
    }
    return FromJson(v);
}

std::string JsonObject::ToString() {
    return ToJson().toStyledString();
}

bool JsonObject::Save(const char *dir) {
    // TODO
    return true;
}

bool JsonObject::Load(const char *dir) {
    // TODO
    return true;
}

