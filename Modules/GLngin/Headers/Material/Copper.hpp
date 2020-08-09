#pragma once

#ifndef GLNGIN_MATERIAL_COPPER_HPP
#define GLNGIN_MATERIAL_COPPER_HPP

#include "API.hpp"
#include "Smooth.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Copper : public Smooth {
public:
    explicit Copper(const std::string (&_names)[6]);
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_COPPER_HPP
