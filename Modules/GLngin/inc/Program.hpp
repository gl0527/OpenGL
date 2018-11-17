#pragma once

#ifndef GLNGIN_PROGRAM_HPP
#define GLNGIN_PROGRAM_HPP

#include "API.hpp"
#include <vector>


namespace GLngin {
namespace Math {
    class Mat4;
    class Vec4;
}   // namespace Math

class Shader;

class GLNGIN_API Program final {
public:
                    Program ();
                    ~Program ();
	
                    Program (const Program&) = delete;
    Program&        operator= (const Program&) = delete;

    void            Init ();
    void            AddShader (const Shader& shader);

    void            Link ();
	
    void            Enable () const;
    void            Disable () const;

    unsigned int    GetID () const;

    bool            SetUniformFloat (const char * uniformName, float value) const;
    bool            SetUniformInt (const char * uniformName, int value) const;
    bool            SetUniformMat4 (const char * uniformName, const Math::Mat4& value) const;
    bool            SetUniformVec4 (const char * uniformName, const Math::Vec4& value) const;

private:
    unsigned int        m_id;
    std::vector<Shader> m_shaders;

    bool                m_inited;
    bool                m_linked;
};

}	// namespace GLngine

#endif	// #ifndef GLNGIN_PROGRAM_HPP
