#pragma once

#ifndef GLNGIN_MATERIAL_SKYBOX_HPP
#define GLNGIN_MATERIAL_SKYBOX_HPP

#include "API.hpp"
#include "Material.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Skybox : public Material {
public:
    Skybox(const std::string (&_names)[6]);

    virtual void Bind() override;
    virtual void Bind(const PerObjectData &pod, const PerFrameData &pfd) override;

private:
    std::string names[6];
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_SKYBOX_HPP
