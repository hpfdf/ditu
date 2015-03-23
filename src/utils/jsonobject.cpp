#include "jsonobject.h"

#include <cstring>
#include <cstdio>

#include "libJson/json.h"

bool JsonObject::FromJson(const Json::Value &) {
    return false;
}

Json::Value JsonObject::ToJson() const {
    return Json::Value();
}

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
    FILE *f = std::fopen(dir, "w");
    if (f == nullptr) {
        return false;
    }
    auto s = ToString();
    std::fwrite(s.data(), sizeof(char), s.length(), f);
    std::fclose(f);
    return true;
}

bool JsonObject::Load(const char *dir) {
    FILE *f = std::fopen(dir, "r");
    if (f == nullptr) {
        return false;
    }
    
    std::fseek(f, 0, SEEK_END);
    auto fsize = std::ftell(f);
    std::rewind(f);
    auto buffer = new char [fsize + 1];
    if (std::fread(buffer, 1, fsize, f) != fsize) {
        delete [] buffer;
        return false;
    }
    if (!FromString(buffer)) {
        delete [] buffer;
        return false;
    }
    delete [] buffer;
    std::fclose(f);
    return true;
}

