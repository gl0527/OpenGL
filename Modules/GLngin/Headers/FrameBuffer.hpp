#pragma once

#ifndef GLNGIN_FRAME_BUFFER_HPP
#define GLNGIN_FRAME_BUFFER_HPP

#include "API.hpp"
#include <string>

namespace GLngin {

class GLNGIN_API FrameBuffer final {
public:
    FrameBuffer();
    ~FrameBuffer();

    void Create(int width, int height);
    void Create(std::string const &name);
    void Destroy();

    void Bind();
    void UnBind();

    void ReSize(unsigned int newWidth, unsigned int newHeight);

    unsigned int GetID() const;
    unsigned int GetColorAttachmentID() const;

    int GetWidth() const;
    int GetHeight() const;

private:
    unsigned int m_id;
    int m_width, m_height;
    unsigned int m_colorAttachmentID, m_depthStencilAttachmentID;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_FRAME_BUFFER_HPP
