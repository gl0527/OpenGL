#pragma once

#ifndef GLNGIN_TEXTURE_CUBE_HPP
#define GLNGIN_TEXTURE_CUBE_HPP

#include "API.hpp"
#include <string>
#include <unordered_map>

namespace GLngin {

class GLNGIN_API TextureCube final {
public:
    static unsigned int GetID(const std::string (&arr)[6]);
    static void DeleteAll();

    TextureCube(const TextureCube&) = delete;
    TextureCube& operator=(const TextureCube&) = delete;

private:
    TextureCube() = default;
    ~TextureCube() = default;

private:
    static std::unordered_map<std::string, unsigned int> pool;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_TEXTURE_CUBE_HPP
