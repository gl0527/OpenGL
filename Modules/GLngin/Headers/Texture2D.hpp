#pragma once

#ifndef GLNGIN_TEXTURE_2D_HPP
#define GLNGIN_TEXTURE_2D_HPP

#include "API.hpp"
#include <string>
#include <unordered_map>

namespace GLngin {

class GLNGIN_API Texture2D final {
public:
    static unsigned int GetID(const std::string &name);
    static void DeleteAll();

    Texture2D(const Texture2D &) = delete;
    Texture2D &operator=(const Texture2D &) = delete;

private:
    Texture2D() = default;
    ~Texture2D() = default;

private:
    static std::unordered_map<std::string, unsigned int> pool;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_TEXTURE_2D_HPP
