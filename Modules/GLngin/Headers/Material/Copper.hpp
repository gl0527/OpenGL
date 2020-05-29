#pragma once

#ifndef GLNGIN_MATERIAL_COPPER_HPP
#define GLNGIN_MATERIAL_COPPER_HPP

#include "API.hpp"
#include "Smooth.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Copper : public Smooth {
public:
    using Smooth::Smooth;

    virtual void Bind() override;
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_COPPER_HPP
