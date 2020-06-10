#pragma once

#ifndef GLNGIN_MATERIAL_MATERIAL_HPP
#define GLNGIN_MATERIAL_MATERIAL_HPP

#include "API.hpp"
#include "Shader.hpp"

namespace GLngin {

struct PerObjectData;
struct PerFrameData;

namespace Material {

class GLNGIN_API Material {
public:
    virtual ~Material();

    virtual void Bind() = 0;
    virtual void Bind(const PerObjectData &pod, const PerFrameData &pfd) = 0;

    void UnBind();

protected:
    Shader shader;
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_MATERIAL_HPP
