#pragma once

#ifndef GLNGIN_TEXTURE_2D_HPP
#define GLNGIN_TEXTURE_2D_HPP

#include "API.hpp"
#include <string>

namespace GLngin {

class GLNGIN_API Texture2D final {
public:
    Texture2D();
    ~Texture2D();

    void Init();
    bool Load(const char *fileName);
    bool Load(const std::string &fileName);

    unsigned int GetID() const;

private:
    unsigned int m_id;
    bool m_inited;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_TEXTURE_2D_HPP
