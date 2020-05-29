#pragma once

#ifndef GLNGIN_MATERIAL_GLASS_HPP
#define GLNGIN_MATERIAL_GLASS_HPP

#include "API.hpp"
#include "Smooth.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Glass : public Smooth {
public:
    using Smooth::Smooth;

    virtual void Bind() override;
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_GLASS_HPP
