#include "Mat4.hpp"

#include <cmath>

#include "Vec3.hpp"
#include "Vec4.hpp"


namespace GLngin {
namespace Math {

Mat4::Mat4 () :
    m_array {{},{},{},{}}
{
}


Mat4::Mat4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) :
    m_array {   {m00, m01, m02, m03},
                {m10, m11, m12, m13},
                {m20, m21, m22, m23},
                {m30, m31, m32, m33}}
{
}


Mat4::Mat4 (const float (&arr)[16])
{
    for (unsigned char i = 0; i < 16; ++i)
        m_array[i/4][i%4] = arr[i];
}


Mat4::Mat4 (const float (&arr)[4][4])
{
    for (unsigned char i = 0; i < 4; ++i)
        for (unsigned char j = 0; j < 4; ++j)
            m_array[i][j] = arr[i][j];
}


Mat4::Mat4 (const Vec3& basisX, const Vec3& basisY, const Vec3& basisZ, const Vec3& translation) :
    m_array {{basisX.x,         basisX.y,       basisX.z,       0.0f},
             {basisY.x,         basisY.y,       basisY.z,       0.0f},
             {basisZ.x,         basisZ.y,       basisZ.z,       0.0f},
             {translation.x,    translation.y,  translation.z,  1.0f}}
{
}


Mat4::Mat4 (const Vec3& basisX, const Vec3& basisY, const Vec3& basisZ, const Vec3& translation, const Vec3& scaling) :
    m_array {{basisX.x * scaling.x,         basisX.y * scaling.y,       basisX.z * scaling.z,       0.0f},
             {basisY.x * scaling.x,         basisY.y * scaling.y,       basisY.z * scaling.z,       0.0f},
             {basisZ.x * scaling.x,         basisZ.y * scaling.y,       basisZ.z * scaling.z,       0.0f},
             {translation.x,                translation.y,              translation.z,              1.0f}}
{
}


Mat4::Mat4 (const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3) :
    m_array {{row0.x, row0.y, row0.z, row0.w},
             {row1.x, row1.y, row1.z, row1.w},
             {row2.x, row2.y, row2.z, row2.w},
             {row3.x, row3.y, row3.z, row3.w}}
{
}


Mat4 Mat4::operator+ (const Mat4& right) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] + right.m_array[i][j];
        }
    }
    return result;
}


Mat4 Mat4::operator- (const Mat4& right) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] - right.m_array[i][j];
        }
    }
    return result;
}


Mat4 Mat4::operator* (const Mat4& right) const
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


Mat4 Mat4::operator* (float scaler) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] * scaler;
        }
    }
    return result;
}


Mat4 Mat4::operator% (const Mat4& right) const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[i][j] * right.m_array[i][j];
        }
    }
    return result;
}


Mat4::operator const float* () const
{
    return &m_array[0][0];
}


Vec4 Mat4::operator[] (unsigned char rowIdx) const
{
    return Vec4 (m_array[rowIdx]);
}


Mat4& Mat4::operator+= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] += right.m_array[i][j];
        }
    }
    return *this;
}


Mat4& Mat4::operator-= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] -= right.m_array[i][j];
        }
    }
    return *this;
}


Mat4& Mat4::operator*= (const Mat4& right)
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


Mat4& Mat4::operator*= (float scaler)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] *= scaler;
        }
    }
    return *this;
}


Mat4& Mat4::operator%= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] *= right.m_array[i][j];
        }
    }
    return *this;
}


Vec4 Mat4::GetRow (unsigned char index) const
{
    return Vec4 (m_array[index]);
}


Vec4 Mat4::GetCol (unsigned char index) const
{
    return Vec4 (m_array[0][index], m_array[1][index], m_array[2][index], m_array[3][index]);
}


Mat4 Mat4::Transpose () const
{
    Mat4 result;
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            result.m_array[i][j] = m_array[j][i];
        }
    }
    return result;
}


float Mat4::Cofactor (unsigned char i,  unsigned char j) const
{
    float m[9];
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


bool Mat4::Invert (Mat4* mat) const
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


Mat4 Mat4::Translate (const Vec3& v) const
{
    Mat4 mat = *this;
    mat.m_array[3][0] += v.x;
    mat.m_array[3][1] += v.y;
    mat.m_array[3][2] += v.z;
    return mat;
}


Mat4 Mat4::Scale (const Vec3& v) const
{
    Mat4 id = Identity ();
    id.m_array[0][0] = v.x;
    id.m_array[1][1] = v.y;
    id.m_array[2][2] = v.z;
    return *this * id;
}


Mat4 Mat4::SetTranslation (const Vec3& translation) const
{
    Mat4 mat = *this;
    mat.m_array[3][0] = translation.x;
    mat.m_array[3][1] = translation.y;
    mat.m_array[3][2] = translation.z;
    return mat;
}


Mat4 Mat4::Translation (const Vec3& position)
{
    Mat4 mat = Identity ();
    mat.m_array[3][0] = position.x;
    mat.m_array[3][1] = position.y;
    mat.m_array[3][2] = position.z;
    return mat;
}


Mat4 Mat4::Rotation (const Vec3& right, const Vec3& up, const Vec3& ahead)
{
    return Mat4 (right, up, ahead, Vec3::Zero ());
}


Mat4 Mat4::Scaling (const Vec3& scaler)
{
    Mat4 mat = Identity ();
    mat.m_array[0][0] = scaler.x;
    mat.m_array[1][1] = scaler.y;
    mat.m_array[2][2] = scaler.z;
    return mat;
}


const Mat4& Mat4::Identity ()
{
    static const Mat4 Identity (1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);

    return Identity;
}


const Mat4& Mat4::Zero ()
{
    static const Mat4 Zero (0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f);

    return Zero;
}


const Mat4& Mat4::One ()
{
    static const Mat4 One ( 1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f, 1.0f);

    return One;
}

}   // namespace Math
}   // namespace GLngin
