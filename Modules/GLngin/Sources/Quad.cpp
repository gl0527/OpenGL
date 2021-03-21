#include "Quad.hpp"

#include "Debug.hpp"
#include "Vec2.hpp"

#include <GL/glew.h>

namespace GLngin {
namespace {

struct Vertex2D {
    Math::Vec2 pos, uv;
};

}  // namespace

Quad::Quad()
    : m_vertexArrayID(0)
    , m_vertexBufferID(0)
    , m_indexBufferID(0)
    , m_inited(false)
{
}

Quad::~Quad()
{
    if (!m_inited) return;

    GL_CALL(glDeleteBuffers(1, &m_indexBufferID));
    GL_CALL(glDeleteBuffers(1, &m_vertexBufferID));
    GL_CALL(glDeleteVertexArrays(1, &m_vertexArrayID));
}

void Quad::Init()
{
    GL_CALL(glGenVertexArrays(1, &m_vertexArrayID));
    GL_CALL(glBindVertexArray(m_vertexArrayID));

    // clang-format off
    constexpr Vertex2D vertices[] = {
        {{-1.0f,  1.0f}, {0.0f, 1.0f}},
        {{ 1.0f,  1.0f}, {1.0f, 1.0f}},
        {{ 1.0f, -1.0f}, {1.0f, 0.0f}},
        {{-1.0f, -1.0f}, {0.0f, 0.0f}},
    };
    constexpr unsigned char indices[] = {
        0, 1, 3, 2
    };
    // clang-format on

    GL_CALL(glGenBuffers(1, &m_vertexBufferID));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL(glGenBuffers(1, &m_indexBufferID));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glBindVertexArray(0));

    m_inited = true;
}

void Quad::Render() const
{
    if (!m_inited) return;

    RenderImpl();
}

void Quad::Render(int lowerLeftX, int lowerLeftY, int width, int height) const
{
    if (!m_inited) return;

    // save current viewport
    int viewPort[4];
    GL_CALL(glGetIntegerv(GL_VIEWPORT, viewPort));

    // modify viewport, and draw into it
    GL_CALL(glViewport(lowerLeftX, lowerLeftY, width, height));
    RenderImpl();

    // reset viewport
    GL_CALL(glViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));
}

void Quad::RenderImpl() const
{
    GL_CALL(glBindVertexArray(m_vertexArrayID));
    GL_CALL(glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, nullptr));
    GL_CALL(glBindVertexArray(0));
}

}  // namespace GLngin
