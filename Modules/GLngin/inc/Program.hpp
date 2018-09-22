#pragma once

#ifndef GLNGIN_PROGRAM_HPP
#define GLNGIN_PROGRAM_HPP

#include "API.hpp"
#include <memory>
#include <map>


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

    void            Init (const std::shared_ptr<Shader>& vertShader,
                          const std::shared_ptr<Shader>& geomShader,
                          const std::shared_ptr<Shader>& fragShader,
                          const std::shared_ptr<Shader>& compShader);

    void            Link ();
	
    void            Enable () const;
    void            Disable () const;

    unsigned int    GetHandle () const;

    bool            SetUniformMat4 (const char * uniformName, const Math::Mat4& value) const;
    bool            SetUniformVec4 (const char * uniformName, const Math::Vec4& value) const;

private:
    unsigned int                                    m_handle;
    std::map<unsigned int, std::shared_ptr<Shader>> m_shaders;

    bool                                            m_inited;
    bool                                            m_linked;
	
    void            AddShader (const std::shared_ptr<Shader>& shader);
};

}	// namespace GLngine

#endif	// #ifndef GLNGIN_PROGRAM_HPP
