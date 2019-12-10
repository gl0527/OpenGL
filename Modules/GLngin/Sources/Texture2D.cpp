#include "Texture2D.hpp"
#include "Debug.hpp"

#include <GL/glew.h>

#include <IL/il.h>
#include <IL/ilu.h>

namespace GLngin {

Texture2D::Texture2D()
    : m_id(0)
    , m_inited(false)
{
}

Texture2D::~Texture2D()
{
    if (!m_inited) return;

    GL_CALL(glDeleteTextures(1, &m_id));
}

void Texture2D::Init()
{
    GL_CALL(glGenTextures(1, &m_id));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    IL_CALL(ilInit());  // TODO ennek nem itt lenne a helye

    m_inited = true;
}

bool Texture2D::Load(const char *fileName)
{
    if (!m_inited) return false;

    unsigned int imageID;
    IL_CALL(ilGenImages(1, &imageID));
    IL_CALL(ilBindImage(imageID));

    bool success = false;
    IL_CALL(success = ilLoadImage(fileName));

    if (!success) return false;

    ILinfo imageInfo;
    IL_CALL(iluGetImageInfo(&imageInfo));
    if (imageInfo.Origin == IL_ORIGIN_UPPER_LEFT) IL_CALL(iluFlipImage());

    IL_CALL(success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE));

    if (!success) return false;

    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));
    GL_CALL(IL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH),
                                 ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT),
                                 ilGetInteger(IL_IMAGE_TYPE), ilGetData())));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    IL_CALL(ilDeleteImages(1, &imageID));
    IL_CALL(ilBindImage(0));

    return true;
}

bool Texture2D::Load(const std::string &fileName)
{
    return Load(fileName.c_str());
}

unsigned int Texture2D::GetID() const
{
    return m_id;
}

}  // namespace GLngin
