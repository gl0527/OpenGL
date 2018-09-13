#pragma once

#ifndef MAT4_HPP
#define MAT4_HPP

#include "API.hpp"


namespace GLngin {

class Vec4;

class GLNGIN_API Mat4 final {
public:
                        Mat4 ();
                        Mat4 (  float m00, float m01, float m02, float m03,
                                float m10, float m11, float m12, float m13,
                                float m20, float m21, float m22, float m23,
                                float m30, float m31, float m32, float m33);
                        Mat4 (float (&arr)[16]);
                        Mat4 (float (&arr)[4][4]);
	
    Mat4                operator+ (const Mat4& right) const;
    Mat4                operator- (const Mat4& right) const;
    Mat4                operator* (const Mat4& right) const;
    Mat4                operator* (float scaler) const;
    Mat4                operator% (const Mat4& right) const;
	
                        operator const float*() const;
    const float*        operator[] (unsigned char rowIdx) const;
	
    void                operator+= (const Mat4& right);
    void                operator-= (const Mat4& right);
    void                operator*= (const Mat4& right);
    void                operator*= (float scaler);
    void                operator%= (const Mat4& right);
	
    Mat4                Transpose () const;
    Mat4                Invert () const;
	
    Mat4                Translate (const Vec4& v) const;
    Mat4                Scale (const Vec4& v) const;

    static const Mat4&  Identity ();
    static const Mat4&  Zero ();
    static const Mat4&  One ();

private:
    float m_array[4][4];
	
    Mat4                InvertImpl () const;
};

}	// namespace GLngine

#endif	// #ifndef MAT4_HPP
