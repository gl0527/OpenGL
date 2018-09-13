#include "Mat4.hpp"
#include "Vec4.hpp"
#include <cmath>


namespace GLngin {

Mat4::Mat4 () :
    m_array {{},{},{},{}}
{
}


Mat4::Mat4(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) :
    m_array {	{m00, m01, m02, m03},
		{m10, m11, m12, m13},
		{m20, m21, m22, m23},
		{m30, m31, m32, m33}}
{
}


Mat4::Mat4 (float (&arr)[16])
{
	for (unsigned char i = 0; i < 16; ++i)
        m_array[i/4][i%4] = arr[i];
}


Mat4::Mat4 (float (&arr)[4][4])
{
    for (unsigned char i = 0; i < 4; ++i)
        for (unsigned char j = 0; j < 4; ++j)
            m_array[i][j] = arr[i][j];
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


Mat4::operator const float*() const
{
    return &m_array[0][0];
}


const float* Mat4::operator[] (unsigned char rowIdx) const
{
    return m_array[rowIdx];
}


void Mat4::operator+= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] += right.m_array[i][j];
		}
	}
}


void Mat4::operator-= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] -= right.m_array[i][j];
		}
	}
}


void Mat4::operator*= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] = 0;
            for (unsigned char k = 0; k < 4; k++)
                m_array[i][j] += m_array[i][k] * right.m_array[k][j];
		}
	}
}


void Mat4::operator*= (float scaler)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] *= scaler;
		}
	}
}


void Mat4::operator%= (const Mat4& right)
{
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            m_array[i][j] *= right.m_array[i][j];
		}
	}
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


Mat4 Mat4::InvertImpl () const
{
	float det;
	float d10, d20, d21, d31, d32, d03;
	Mat4 inv;
	
	/* Inverse = adjoint / det. (See linear algebra texts.)*/
	
	/* pre-compute 2x2 dets for last two rows when computing */
	/* cofactors of first two rows. */
    d10 = (m_array[0][2]*m_array[1][3]-m_array[0][3]*m_array[1][2]);
    d20 = (m_array[0][2]*m_array[2][3]-m_array[0][3]*m_array[2][2]);
    d21 = (m_array[1][2]*m_array[2][3]-m_array[1][3]*m_array[2][2]);
    d31 = (m_array[1][2]*m_array[3][3]-m_array[1][3]*m_array[3][2]);
    d32 = (m_array[2][2]*m_array[3][3]-m_array[2][3]*m_array[3][2]);
    d03 = (m_array[3][2]*m_array[0][3]-m_array[3][3]*m_array[0][2]);
	
    inv.m_array[0][0] =  (m_array[1][1] * d32 - m_array[2][1] * d31 + m_array[3][1] * d21);
    inv.m_array[0][1] = -(m_array[0][1] * d32 + m_array[2][1] * d03 + m_array[3][1] * d20);
    inv.m_array[0][2] =  (m_array[0][1] * d31 + m_array[1][1] * d03 + m_array[3][1] * d10);
    inv.m_array[0][3] = -(m_array[0][1] * d21 - m_array[1][1] * d20 + m_array[2][1] * d10);
	
	/* Compute determinant as early as possible using these cofactors. */
    det = m_array[0][0] * inv.m_array[0][0] + m_array[1][0] * inv.m_array[0][1] + m_array[2][0] * inv.m_array[0][2] + m_array[3][0] * inv.m_array[0][3];
	
	/* Run singularity test. */
    if (fabsf (det) < 1e-6f)
		return Identity ();

    float invDet = 1.0f / det;
    /* Compute rest of inverse. */
    inv.m_array[0][0] *= invDet;
    inv.m_array[0][1] *= invDet;
    inv.m_array[0][2] *= invDet;
    inv.m_array[0][3] *= invDet;

    inv.m_array[1][0] = -(m_array[1][0] * d32 - m_array[2][0] * d31 + m_array[3][0] * d21) * invDet;
    inv.m_array[1][1] =  (m_array[0][0] * d32 + m_array[2][0] * d03 + m_array[3][0] * d20) * invDet;
    inv.m_array[1][2] = -(m_array[0][0] * d31 + m_array[1][0] * d03 + m_array[3][0] * d10) * invDet;
    inv.m_array[1][3] =  (m_array[0][0] * d21 - m_array[1][0] * d20 + m_array[2][0] * d10) * invDet;

    /* Pre-compute 2x2 dets for first two rows when computing */
    /* cofactors of last two rows. */
    d10 = m_array[0][0]*m_array[1][1]-m_array[0][1]*m_array[1][0];
    d20 = m_array[0][0]*m_array[2][1]-m_array[0][1]*m_array[2][0];
    d21 = m_array[1][0]*m_array[2][1]-m_array[1][1]*m_array[2][0];
    d31 = m_array[1][0]*m_array[3][1]-m_array[1][1]*m_array[3][0];
    d32 = m_array[2][0]*m_array[3][1]-m_array[2][1]*m_array[3][0];
    d03 = m_array[3][0]*m_array[0][1]-m_array[3][1]*m_array[0][0];

    inv.m_array[2][0] =  (m_array[1][3] * d32 - m_array[2][3] * d31 + m_array[3][3] * d21) * invDet;
    inv.m_array[2][1] = -(m_array[0][3] * d32 + m_array[2][3] * d03 + m_array[3][3] * d20) * invDet;
    inv.m_array[2][2] =  (m_array[0][3] * d31 + m_array[1][3] * d03 + m_array[3][3] * d10) * invDet;
    inv.m_array[2][3] = -(m_array[0][3] * d21 - m_array[1][3] * d20 + m_array[2][3] * d10) * invDet;
    inv.m_array[3][0] = -(m_array[1][2] * d32 - m_array[2][2] * d31 + m_array[3][2] * d21) * invDet;
    inv.m_array[3][1] =  (m_array[0][2] * d32 + m_array[2][2] * d03 + m_array[3][2] * d20) * invDet;
    inv.m_array[3][2] = -(m_array[0][2] * d31 + m_array[1][2] * d03 + m_array[3][2] * d10) * invDet;
    inv.m_array[3][3] =  (m_array[0][2] * d21 - m_array[1][2] * d20 + m_array[2][2] * d10) * invDet;

    return inv;
}


Mat4 Mat4::Invert() const
{
    if (m_array[0][3] != 0.0f || m_array[1][3] != 0.0f || m_array[2][3] != 0.0f || m_array[3][3] != 1.0f) {
	   return InvertImpl ();
	}

	Mat4 inv;

	/* Inverse = adjoint / det. */
    inv.m_array[0][0] = m_array[1][1] * m_array[2][2] - m_array[2][1] * m_array[1][2];
    inv.m_array[0][1] = m_array[2][1] * m_array[0][2] - m_array[0][1] * m_array[2][2];
    inv.m_array[0][2] = m_array[0][1] * m_array[1][2] - m_array[1][1] * m_array[0][2];

	/* Compute determinant as early as possible using these cofactors. */
    float det = m_array[0][0] * inv.m_array[0][0] + m_array[1][0] * inv.m_array[0][1] + m_array[2][0] * inv.m_array[0][2];

	/* Run singularity test. */
    if (fabsf (det) < 1e-6f)
	   return Identity ();

    float d10, d20, d21, d31, d32, d03;
    float im00, im10, im20, im30;

    det = 1.0f / det;

    /* Compute rest of inverse. */
    inv.m_array[0][0] *= det;
    inv.m_array[0][1] *= det;
    inv.m_array[0][2] *= det;
    inv.m_array[0][3]  = 0.0f;

    im00 = m_array[0][0] * det;
    im10 = m_array[1][0] * det;
    im20 = m_array[2][0] * det;
    im30 = m_array[3][0] * det;
    inv.m_array[1][0] = im20 * m_array[1][2] - im10 * m_array[2][2];
    inv.m_array[1][1] = im00 * m_array[2][2] - im20 * m_array[0][2];
    inv.m_array[1][2] = im10 * m_array[0][2] - im00 * m_array[1][2];
    inv.m_array[1][3] = 0.0f;

    /* Pre-compute 2x2 dets for first two rows when computing */
    /* cofactors of last two rows. */
    d10 = im00 * m_array[1][1] - m_array[0][1] * im10;
    d20 = im00 * m_array[2][1] - m_array[0][1] * im20;
    d21 = im10 * m_array[2][1] - m_array[1][1] * im20;
    d31 = im10 * m_array[3][1] - m_array[1][1] * im30;
    d32 = im20 * m_array[3][1] - m_array[2][1] * im30;
    d03 = im30 * m_array[0][1] - m_array[3][1] * im00;

    inv.m_array[2][0] = d21;
    inv.m_array[2][1] = -d20;
    inv.m_array[2][2] = d10;
    inv.m_array[2][3] = 0.0f;

    inv.m_array[3][0] = -(m_array[1][2] * d32 - m_array[2][2] * d31 + m_array[3][2] * d21);
    inv.m_array[3][1] = (m_array[0][2] * d32 + m_array[2][2] * d03 + m_array[3][2] * d20);
    inv.m_array[3][2] = -(m_array[0][2] * d31 + m_array[1][2] * d03 + m_array[3][2] * d10);
    inv.m_array[3][3] = 1.0f;

    return inv;
}


Mat4 Mat4::Translate (const Vec4& v) const
{
	Mat4 id = Identity ();
    id.m_array[3][0] = v[0];
    id.m_array[3][1] = v[1];
    id.m_array[3][2] = v[2];
	return *this * id;
}


Mat4 Mat4::Scale (const Vec4& v) const
{
	Mat4 id = Identity ();
    id.m_array[0][0] = v[0];
    id.m_array[1][1] = v[1];
    id.m_array[2][2] = v[2];
	return *this * id;
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

}	// namespace GLngine
