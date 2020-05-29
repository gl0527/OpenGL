#pragma once

#ifndef GLNGIN_MATERIAL_SILVER_HPP
#define GLNGIN_MATERIAL_SILVER_HPP

#include "API.hpp"
#include "Smooth.hpp"

namespace GLngin {
namespace Material {

class Silver : public Smooth {
public:
    using Smooth::Smooth;

    virtual void Bind() override;
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_SILVER_HPP
