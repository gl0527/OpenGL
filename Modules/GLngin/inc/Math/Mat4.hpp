#pragma once

#ifndef GLNGIN_MATH_MAT4_HPP
#define GLNGIN_MATH_MAT4_HPP

#include "API.hpp"


namespace GLngin {
namespace Math {

class Vec3;
class Vec4;

class GLNGIN_API Mat4 final {
public:
                        Mat4 ();
                        Mat4 (  float m00, float m01, float m02, float m03,
                                float m10, float m11, float m12, float m13,
                                float m20, float m21, float m22, float m23,
                                float m30, float m31, float m32, float m33);
                        Mat4 (const float (&arr)[16]);
                        Mat4 (const float (&arr)[4][4]);
                        Mat4 (const Vec3& basisX, const Vec3& basisY, const Vec3& basisZ, const Vec3& translation);
                        Mat4 (const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3);

    Mat4                operator+ (const Mat4& right) const;
    Mat4                operator- (const Mat4& right) const;
    Mat4                operator* (const Mat4& right) const;
    Mat4                operator* (float scaler) const;
    Mat4                operator% (const Mat4& right) const;

                        operator const float* () const;
    Vec4                operator[] (unsigned char rowIdx) const;

    Mat4&               operator+= (const Mat4& right);
    Mat4&               operator-= (const Mat4& right);
    Mat4&               operator*= (const Mat4& right);
    Mat4&               operator*= (float scaler);
    Mat4&               operator%= (const Mat4& right);

    Vec4                GetRow (unsigned char index) const;
    Vec4                GetCol (unsigned char index) const;

    Mat4                Transpose () const;
    bool                Invert (Mat4* mat) const;

    Mat4                Translate (const Vec3& v) const;
    Mat4                Scale (const Vec3& v) const;

    Mat4                SetTranslation (const Vec3& translation) const;

    static Mat4         Translation (const Vec3& position);
    static Mat4         Rotation (const Vec3& right, const Vec3& up, const Vec3& ahead);
    static Mat4         Scaling (const Vec3& scaler);

    static const Mat4&  Identity ();
    static const Mat4&  Zero ();
    static const Mat4&  One ();

private:
    float m_array[4][4];

    float               Cofactor (unsigned char i,  unsigned char j) const;
};

}   // namespace Math
}   // namespace GLngine

#endif  // #ifndef GLNGIN_MATH_MAT4_HPP
