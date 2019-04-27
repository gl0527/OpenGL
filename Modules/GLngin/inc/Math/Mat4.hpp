#pragma once

#ifndef GLNGIN_MATH_MAT4_HPP
#define GLNGIN_MATH_MAT4_HPP

#include "API.hpp"
#include <cmath>
#include "Vec3.hpp"
#include "Vec4.hpp"


namespace GLngin {
namespace Math {

class GLNGIN_API Mat4 final {
public:
    constexpr                       Mat4 ();
    constexpr                       Mat4 (  float m00, float m01, float m02, float m03,
                                            float m10, float m11, float m12, float m13,
                                            float m20, float m21, float m22, float m23,
                                            float m30, float m31, float m32, float m33);
    constexpr                       Mat4 (const float (&arr)[16]);
    constexpr                       Mat4 (const float (&arr)[4][4]);
    constexpr                       Mat4 (const Vec3& basisX, const Vec3& basisY, const Vec3& basisZ, const Vec3& translation);
    constexpr                       Mat4 (const Vec3& basisX, const Vec3& basisY, const Vec3& basisZ, const Vec3& translation, const Vec3& scaling);
    constexpr                       Mat4 (const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3);

    constexpr Mat4                  operator+ (const Mat4& right) const;
    constexpr Mat4                  operator- (const Mat4& right) const;
    constexpr Mat4                  operator* (const Mat4& right) const;
    constexpr Mat4                  operator* (float scaler) const;
    constexpr Mat4                  operator% (const Mat4& right) const;

    constexpr                       operator const float* () const;
    constexpr Vec4                  operator[] (unsigned char rowIdx) const;

    constexpr Mat4&                 operator+= (const Mat4& right);
    constexpr Mat4&                 operator-= (const Mat4& right);
    constexpr Mat4&                 operator*= (const Mat4& right);
    constexpr Mat4&                 operator*= (float scaler);
    constexpr Mat4&                 operator%= (const Mat4& right);

    constexpr Vec4                  GetRow (unsigned char index) const;
    constexpr Vec4                  GetCol (unsigned char index) const;

    constexpr Mat4                  Transpose () const;
    constexpr bool                  Invert (Mat4* mat) const;

    constexpr Mat4                  Translate (const Vec3& v) const;
    inline Mat4                     Scale (const Vec3& v) const;

    constexpr Mat4                  SetTranslation (const Vec3& translation) const;

    inline static Mat4              Translation (const Vec3& position);
    inline static Mat4              Rotation (const Vec3& right, const Vec3& up, const Vec3& ahead);
    inline static Mat4              Scaling (const Vec3& scaler);

    inline static const Mat4&       Identity ();
    inline static const Mat4&       Zero ();
    inline static const Mat4&       One ();

private:
    float m_array[4][4];

    constexpr float               Cofactor (unsigned char i,  unsigned char j) const;
};


constexpr Mat4::Mat4 () :
    m_array {{},{},{},{}}
{
}


constexpr Mat4::Mat4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) :
    m_array {   {m00, m01, m02, m03},
                {m10, m11, m12, m13},
                {m20, m21, m22, m23},
                {m30, m31, m32, m33}}
{
}


constexpr Mat4::Mat4 (const float (&arr)[16]) :
    m_array {   {arr[0], arr[1], arr[2], arr[3]},
                {arr[4], arr[5], arr[6], arr[7]},
                {arr[8], arr[9], arr[10], arr[11]},
                {arr[12], arr[13], arr[14], arr[15]}}
{
}


constexpr Mat4::Mat4 (const float (&arr)[4][4]) :
    m_array {   {arr[0][0], arr[0][1], arr[0][2], arr[0][3]},
                {arr[1][0], arr[1][1], arr[1][2], arr[1][3]},
                {arr[2][0], arr[2][1], arr[2][2], arr[2][3]},
                {arr[3][0], arr[3][1], arr[3][2], arr[3][3]}}
{
}


constexpr Mat4::Mat4 (const Vec3& basisX, const Vec3& basisY, const Vec3& basisZ, const Vec3& translation) :
    m_array {{basisX.x,         basisX.y,       basisX.z,       0.0f},
             {basisY.x,         basisY.y,       basisY.z,       0.0f},
             {basisZ.x,         basisZ.y,       basisZ.z,       0.0f},
             {translation.x,    translation.y,  translation.z,  1.0f}}
{
}


constexpr Mat4::Mat4 (const Vec3& basisX, const Vec3& basisY, const Vec3& basisZ, const Vec3& translation, const Vec3& scaling) :
    m_array {{basisX.x * scaling.x,         basisX.y * scaling.y,       basisX.z * scaling.z,       0.0f},
             {basisY.x * scaling.x,         basisY.y * scaling.y,       basisY.z * scaling.z,       0.0f},
             {basisZ.x * scaling.x,         basisZ.y * scaling.y,       basisZ.z * scaling.z,       0.0f},
             {translation.x,                translation.y,              translation.z,              1.0f}}
{
}


constexpr Mat4::Mat4 (const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3) :
    m_array {{row0.x, row0.y, row0.z, row0.w},
             {row1.x, row1.y, row1.z, row1.w},
             {row2.x, row2.y, row2.z, row2.w},
             {row3.x, row3.y, row3.z, row3.w}}
{
}


constexpr Mat4 Mat4::operator+ (const Mat4& right) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] + right.m_array[i][j];
        }
    }
    return result;
}


constexpr Mat4 Mat4::operator- (const Mat4& right) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] - right.m_array[i][j];
        }
    }
    return result;
}


constexpr Mat4 Mat4::operator* (const Mat4& right) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = 0;
            for (unsigned char k = 0; k < 4; k++)
                result.m_array[i][j] += m_array[i][k] * right.m_array[k][j];
        }
    }
    return result;
}


constexpr Mat4 Mat4::operator* (float scaler) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] * scaler;
        }
    }
    return result;
}


constexpr Mat4 Mat4::operator% (const Mat4& right) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] * right.m_array[i][j];
        }
    }
    return result;
}


constexpr Mat4::operator const float* () const
{
    return &m_array[0][0];
}


constexpr Vec4 Mat4::operator[] (unsigned char rowIdx) const
{
    return Vec4 (m_array[rowIdx]);
}


constexpr Mat4& Mat4::operator+= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] += right.m_array[i][j];
        }
    }
    return *this;
}


constexpr Mat4& Mat4::operator-= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] -= right.m_array[i][j];
        }
    }
    return *this;
}


constexpr Mat4& Mat4::operator*= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] = 0;
            for (unsigned char k = 0; k < 4; k++)
                m_array[i][j] += m_array[i][k] * right.m_array[k][j];
        }
    }
    return *this;
}


constexpr Mat4& Mat4::operator*= (float scaler)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] *= scaler;
        }
    }
    return *this;
}


constexpr Mat4& Mat4::operator%= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] *= right.m_array[i][j];
        }
    }
    return *this;
}


constexpr Vec4 Mat4::GetRow (unsigned char index) const
{
    return Vec4 (m_array[index]);
}


constexpr Vec4 Mat4::GetCol (unsigned char index) const
{
    return Vec4 (m_array[0][index], m_array[1][index], m_array[2][index], m_array[3][index]);
}


constexpr Mat4 Mat4::Transpose () const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[j][i];
        }
    }
    return result;
}


constexpr float Mat4::Cofactor (unsigned char i,  unsigned char j) const
{
    float m[9] = {};
    unsigned char siz = 0;

    for (unsigned char row = 0; row < 4; ++row) {
        for (unsigned char col = 0; col < 4; ++col) {
            if (row == i || col == j)
                continue;
            m[siz++] = m_array[row][col];
        }
    }

    float minor =   m[0] * (m[4] * m[8] - m[5] * m[7]) -
                    m[1] * (m[3] * m[8] - m[5] * m[6]) +
                    m[2] * (m[3] * m[7] - m[4] * m[6]);

    return (i + j) % 2 == 0 ? minor : -minor;
}


constexpr bool Mat4::Invert (Mat4* mat) const
{
    Mat4 comatrix;
    float det = 0.0f;

    for (unsigned char i = 0; i < 4; ++i) {
        for (unsigned char j = 0; j < 4; ++j) {
            comatrix.m_array[i][j] = Cofactor (i, j);
        }
        if (i == 0) {
            det = Vec4 (m_array[0]).Dot (comatrix.m_array[0]);
            if (fabsf (det) < 1e-6f)
               return false;
        }
    }

    *mat = comatrix.Transpose () * (1 / det);
    return true;
}


constexpr Mat4 Mat4::Translate (const Vec3& v) const
{
    Mat4 mat = *this;
    mat.m_array[3][0] += v.x;
    mat.m_array[3][1] += v.y;
    mat.m_array[3][2] += v.z;
    return mat;
}


inline Mat4 Mat4::Scale (const Vec3& v) const
{
    Mat4 id = Identity ();
    id.m_array[0][0] = v.x;
    id.m_array[1][1] = v.y;
    id.m_array[2][2] = v.z;
    return *this * id;
}


constexpr Mat4 Mat4::SetTranslation (const Vec3& translation) const
{
    Mat4 mat = *this;
    mat.m_array[3][0] = translation.x;
    mat.m_array[3][1] = translation.y;
    mat.m_array[3][2] = translation.z;
    return mat;
}


inline Mat4 Mat4::Translation (const Vec3& position)
{
    Mat4 mat = Identity ();
    mat.m_array[3][0] = position.x;
    mat.m_array[3][1] = position.y;
    mat.m_array[3][2] = position.z;
    return mat;
}


inline Mat4 Mat4::Rotation (const Vec3& right, const Vec3& up, const Vec3& ahead)
{
    return Mat4 (right, up, ahead, Vec3::Zero ());
}


inline Mat4 Mat4::Scaling (const Vec3& scaler)
{
    Mat4 mat = Identity ();
    mat.m_array[0][0] = scaler.x;
    mat.m_array[1][1] = scaler.y;
    mat.m_array[2][2] = scaler.z;
    return mat;
}


inline const Mat4& Mat4::Identity ()
{
    static const Mat4 Identity (1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);

    return Identity;
}


inline const Mat4& Mat4::Zero ()
{
    static const Mat4 Zero (0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f);

    return Zero;
}


inline const Mat4& Mat4::One ()
{
    static const Mat4 One ( 1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f);

    return One;
}

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_MAT4_HPP
