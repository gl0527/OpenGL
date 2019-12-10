#pragma once

#ifndef GLNGIN_GEOMETRY_HPP
#define GLNGIN_GEOMETRY_HPP

#include "API.hpp"

namespace GLngin {

class GLNGIN_API Geometry {
public:
    virtual ~Geometry();

    void Init();
    void Draw();

protected:
    unsigned int vao, numOfVertices;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_GEOMETRY_HPP
