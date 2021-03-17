#include "Texture2D.hpp"
#include "Debug.hpp"

#include <GL/glew.h>

#include <IL/il.h>
#include <IL/ilu.h>

namespace GLngin {

std::unordered_map<std::string, unsigned int> Texture2D::pool;

unsigned int Texture2D::GetID(const std::string &name)
{
    // if (auto it = pool.find(name); it != pool.end()) {
    //     return it->second;
    // } else {
    unsigned int id;
    GL_CALL(glGenTextures(1, &id));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, id));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    unsigned int imageID;
    IL_CALL(ilGenImages(1, &imageID));
    IL_CALL(ilBindImage(imageID));

    bool success = false;
    IL_CALL(success = ilLoadImage(name.c_str()));

    if (!success) {
        return 0;
    }

    ILinfo imageInfo;
    IL_CALL(iluGetImageInfo(&imageInfo));
    if (imageInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
        IL_CALL(iluFlipImage());
    }

    IL_CALL(success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE));

    if (!success) {
        return 0;
    }

    GL_CALL(glBindTexture(GL_TEXTURE_2D, id));
    GL_CALL(IL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH),
                                 ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT),
                                 ilGetInteger(IL_IMAGE_TYPE), ilGetData())));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    IL_CALL(ilDeleteImages(1, &imageID));
    IL_CALL(ilBindImage(0));

    pool[name] = id;

    return id;
    // }
}

void Texture2D::DeleteAll()
{
    for (auto &[k, v] : pool) {
        GL_CALL(glDeleteTextures(1, &v));
    }
    pool.clear();
}

}  // namespace GLngin
