#include "Texture2D.hpp"

#include "Debug.hpp"


namespace GLngin {

Texture2D::Texture2D (int width, int height) :
    m_handle (0),
    m_width (width),
    m_height (height),
    m_inited (false)
{
}


Texture2D::~Texture2D ()
{
    if (!m_inited)
        return;

    GL_CALL (glDeleteTextures (1, &m_handle));
}


void Texture2D::Init ()
{
    GL_CALL (glGenTextures (1, &m_handle));
    GL_CALL (glBindTexture (GL_TEXTURE_2D, m_handle));

    GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CALL (glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, nullptr));

    GL_CALL (glBindTexture (GL_TEXTURE_2D, 0));

    m_inited = true;
}


unsigned int Texture2D::GetHandle () const
{
    return m_handle;
}


int Texture2D::GetWidth () const
{
    return m_width;
}


int Texture2D::GetHeight () const
{
    return m_height;
}


void Texture2D::SetData (float * data)
{
    if (!m_inited)
        return;

    GL_CALL (glBindTexture (GL_TEXTURE_2D, m_handle));
    GL_CALL (glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, data));
    GL_CALL (glBindTexture (GL_TEXTURE_2D, 0));
}

}   // namespace GLngin
