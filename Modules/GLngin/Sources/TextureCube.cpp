#include "TextureCube.hpp"

#include "Debug.hpp"
#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>

namespace GLngin {

TextureCube::TextureCube()
    : m_id(0)
    , m_inited(false)
{
}

TextureCube::~TextureCube()
{
    if (!m_inited) return;

    GL_CALL(glDeleteTextures(1, &m_id));
}

void TextureCube::Init()
{
    GL_CALL(glGenTextures(1, &m_id));
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));

    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

    IL_CALL(ilInit());  // TODO ennek nem itt lenne a helye

    m_inited = true;
}

bool TextureCube::Load(const char *right, const char *left, const char *top, const char *bottom, const char *front,
                       const char *back)
{
    const char *arr[] = {right, left, top, bottom, front, back};
    return Load(arr);
}

bool TextureCube::Load(const std::string &right, const std::string &left, const std::string &top,
                       const std::string &bottom, const std::string &front, const std::string &back)
{
    const char *arr[] = {right.c_str(), left.c_str(), top.c_str(), bottom.c_str(), front.c_str(), back.c_str()};
    return Load(arr);
}

bool TextureCube::Load(const char *(&arr)[6])
{
    if (!m_inited) return false;

    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));

    for (unsigned char i = 0; i < 6; ++i) {
        unsigned int imageID;
        IL_CALL(ilGenImages(1, &imageID));
        IL_CALL(ilBindImage(imageID));

        bool success = false;
        IL_CALL(success = ilLoadImage(arr[i]));

        if (!success) return false;

        ILinfo imageInfo;
        IL_CALL(iluGetImageInfo(&imageInfo));
        IL_CALL(iluFlipImage());
        if (i == 2)  // top image
            IL_CALL(iluRotate(-90));
        else if (i == 3)  // bottom image
            IL_CALL(iluRotate(90));

        IL_CALL(success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE));

        if (!success) return false;

        GL_CALL(IL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, ilGetInteger(IL_IMAGE_FORMAT),
                                     ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
                                     ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData())));

        IL_CALL(ilDeleteImages(1, &imageID));
        IL_CALL(ilBindImage(0));
    }

    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

    return true;
}

unsigned int TextureCube::GetID() const
{
    return m_id;
}

}  // namespace GLngin
