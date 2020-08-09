#pragma once

#ifndef GLNGIN_MATERIAL_DIAMOND_HPP
#define GLNGIN_MATERIAL_DIAMOND_HPP

#include "API.hpp"
#include "Smooth.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Diamond : public Smooth {
public:
    explicit Diamond(const std::string (&_names)[6]);
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_DIAMOND_HPP
