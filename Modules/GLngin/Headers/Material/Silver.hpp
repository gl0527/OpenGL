#pragma once

#ifndef GLNGIN_MATERIAL_SILVER_HPP
#define GLNGIN_MATERIAL_SILVER_HPP

#include "API.hpp"
#include "Smooth.hpp"

namespace GLngin {
namespace Material {

class GLNGIN_API Silver : public Smooth {
public:
    explicit Silver(const std::string (&_names)[6]);
};

}  // namespace Material
}  // namespace GLngin

#endif  // #ifndef GLNGIN_MATERIAL_SILVER_HPP
