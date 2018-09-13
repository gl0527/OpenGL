#pragma once

#ifndef VEC4_HPP
#define VEC4_HPP

#include "API.hpp"


namespace GLngin {

class Mat4;

class GLNGIN_API Vec4 final {
public:
    explicit            Vec4 (float x=0.0f, float y=0.0f, float z=0.0f, float w=1.0f);
                        Vec4 (float (&vec)[4]);

    Vec4&               operator+ ();
    Vec4                operator+ (const Vec4& vec) const;
    Vec4&               operator+= (const Vec4& vec);

    Vec4                operator- ();
    Vec4                operator- (const Vec4& vec) const;
    Vec4&               operator-= (const Vec4& vec);

    Vec4&               operator*= (float scalar);
    Vec4                operator* (float scalar) const;
    Vec4                operator* (const Mat4& mat) const;

    Vec4&               operator/= (float scalar);
    Vec4                operator/ (float scalar) const;

    float               Dot (const Vec4& vec) const;
    Vec4                Hadamard (const Vec4& vec) const;

    float               operator[] (unsigned char idx) const;
    float&              operator[] (unsigned char idx);

                        operator const float* () const;

    static const Vec4&  Zero ();
    static const Vec4&  One ();
    static const Vec4&  UnitX ();
    static const Vec4&  UnitY ();
    static const Vec4&  UnitZ ();
    static const Vec4&  NegativeUnitX ();
    static const Vec4&  NegativeUnitY ();
    static const Vec4&  NegativeUnitZ ();

private:
    float m_array[4];

public:
    float& x;
    float& y;
    float& z;
    float& w;
};

}	// namespace GLngine

#endif	// #ifndef VEC4_HPP
