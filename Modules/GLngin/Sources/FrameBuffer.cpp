#include "FrameBuffer.hpp"

#include <GL/glew.h>

#include "Debug.hpp"
#include "Texture2D.hpp"

namespace GLngin {

FrameBuffer::FrameBuffer()
    : m_id(0)
    , m_width(0)
    , m_height(0)
    , m_colorAttachmentID(0)
    , m_depthStencilAttachmentID(0)
{
}

FrameBuffer::~FrameBuffer()
{
    if (m_id != 0) {
        Destroy();
    }
}

void FrameBuffer::Create(int width, int height)
{
    if (m_id != 0) {
        Destroy();
    }
    GL_CALL(glGenFramebuffers(1, &m_id));

    m_width = width;
    m_height = height;

    // create color attachment texture
    GL_CALL(glGenTextures(1, &m_colorAttachmentID));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_colorAttachmentID));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // create depth and stencil attachment
    GL_CALL(glGenRenderbuffers(1, &m_depthStencilAttachmentID));
    GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilAttachmentID));
    GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height));

    // attach the attachments to the framebuffer
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
    GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachmentID, 0));
    GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                                      m_depthStencilAttachmentID));

    // check if the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG("Framebuffer is not complete.");
    }

    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Create(std::string const &name)
{
    if (m_id != 0) {
        Destroy();
    }
    GL_CALL(glGenFramebuffers(1, &m_id));

    // create color attachment texture
    m_colorAttachmentID = Texture2D::GetID(name);

    // acquiring dimensions of the loaded texture
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_colorAttachmentID));
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_height);
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    // create depth and stencil attachment
    GL_CALL(glGenRenderbuffers(1, &m_depthStencilAttachmentID));
    GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilAttachmentID));
    GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height));

    // attach the attachments to the framebuffer
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
    GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachmentID, 0));
    GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                                      m_depthStencilAttachmentID));

    // check if the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG("Framebuffer is not complete.");
    }

    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Destroy()
{
    GL_CALL(glDeleteRenderbuffers(1, &m_depthStencilAttachmentID));
    GL_CALL(glDeleteTextures(1, &m_colorAttachmentID));
    GL_CALL(glDeleteFramebuffers(1, &m_id));
}

void FrameBuffer::Bind()
{
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
    GL_CALL(glViewport(0, 0, m_width, m_height));
}

void FrameBuffer::UnBind()
{
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::ReSize(unsigned int newWidth, unsigned int newHeight)
{
    if (newWidth == 0 || newHeight == 0 || newWidth > 8192 || newHeight > 8192) {
        LOG("Invalid width or height at the resizing of framebuffer");
        return;
    }
    Create(newWidth, newHeight);
}

unsigned int FrameBuffer::GetID() const
{
    return m_id;
}

unsigned int FrameBuffer::GetColorAttachmentID() const
{
    return m_colorAttachmentID;
}

int FrameBuffer::GetWidth() const
{
    return m_width;
}

int FrameBuffer::GetHeight() const
{
    return m_height;
}

}  // namespace GLngin
