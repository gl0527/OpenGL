#pragma once

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "API.hpp"
#include <memory>
#include <map>


namespace GLngin {

class Mat4;
class Shader;
class Vec4;

class GLNGIN_API Program final {
public:
                Program (	const std::shared_ptr<Shader>& vertShader,
                            const std::shared_ptr<Shader>& geomShader,
                            const std::shared_ptr<Shader>& fragShader,
                            const std::shared_ptr<Shader>& compShader);
                ~Program ();
	
                Program (const Program&) = delete;
    Program&    operator= (const Program&) = delete;
	
    void        Bind () const;
    void        UnBind () const;

    bool        SetMat4 (const char * uniformName, const Mat4& value) const;
    bool        SetVec4 (const char * uniformName, const Vec4& value) const;

private:
    unsigned int                                    m_handle;
    std::map<unsigned int, std::shared_ptr<Shader>> m_shaders;
	
    void        AddShader (const std::shared_ptr<Shader>& shader);
};

}	// namespace GLngine

#endif	// #ifndef PROGRAM_HPP
