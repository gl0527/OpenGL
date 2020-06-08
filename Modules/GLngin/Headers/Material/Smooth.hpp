#pragma once

#ifndef GLNGIN_MATERIAL_SMOOTH_HPP
#define GLNGIN_MATERIAL_SMOOTH_HPP

#include "API.hpp"
#include "Material.hpp"
#include "Vec3.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Smooth : public Material {
public:
    Smooth(const std::string (&_names)[6], const Math::Vec3 &_idxOfRefr, const Math::Vec3 &_absorptCoeff);

    virtual void Bind() override;
    virtual void Bind(const PerObjectData &pod, const PerFrameData &pfd) override;

protected:
    std::string names[6];
    Math::Vec3 idxOfRefr;
    Math::Vec3 absorptCoeff;
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_SMOOTH_HPP
