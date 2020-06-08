#pragma once

#ifndef GLNGIN_MATERIAL_GOLD_HPP
#define GLNGIN_MATERIAL_GOLD_HPP

#include "API.hpp"
#include "Smooth.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Gold : public Smooth {
public:
    Gold(const std::string (&_names)[6]);
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_GOLD_HPP