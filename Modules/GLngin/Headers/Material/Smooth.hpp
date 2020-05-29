#pragma once

#ifndef GLNGIN_MATERIAL_SMOOTH_HPP
#define GLNGIN_MATERIAL_SMOOTH_HPP

#include "API.hpp"
#include "Material.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Smooth : public Material {
public:
    Smooth(const std::string (&_names)[6]);

    virtual void Bind(const PerObjectData &pod, const PerFrameData &pfd) override;

protected:
    std::string names[6];
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_SMOOTH_HPP
