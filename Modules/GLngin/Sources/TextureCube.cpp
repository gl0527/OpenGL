#include "TextureCube.hpp"

#include "Debug.hpp"
#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>

namespace GLngin {

std::unordered_map<std::string, unsigned int> TextureCube::pool;

unsigned int TextureCube::GetID(const std::string (&arr)[6])
{
    std::string name;
    for (const std::string& s : arr) {
        name += s;
    }

    if (auto it = pool.find(name); it != pool.end()) {
        return it->second;
    } else {
        unsigned int id;
        GL_CALL(glGenTextures(1, &id));
        GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, id));

        GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

        GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

        GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, id));

        for (unsigned char i = 0; i < 6; ++i) {
            unsigned int imageID;
            IL_CALL(ilGenImages(1, &imageID));
            IL_CALL(ilBindImage(imageID));

            bool success = false;
            const char *cstr = arr[i].c_str();
            IL_CALL(success = ilLoadImage(cstr));

            if (!success) {
                return 0;
            }

            ILinfo imageInfo;
            IL_CALL(iluGetImageInfo(&imageInfo));
            IL_CALL(iluFlipImage());
            if (i == 2)  // top image
                IL_CALL(iluRotate(-90));
            else if (i == 3)  // bottom image
                IL_CALL(iluRotate(90));

            IL_CALL(success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE));

            if (!success) {
                return 0;
            }

            GL_CALL(IL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, ilGetInteger(IL_IMAGE_FORMAT),
                                        ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
                                        ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData())));

            IL_CALL(ilDeleteImages(1, &imageID));
            IL_CALL(ilBindImage(0));
        }

        GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

        pool[name] = id;

        return id;
    }
}

void TextureCube::DeleteAll()
{
    for (auto& [k, v] : pool) {
        GL_CALL(glDeleteTextures(1, &v));
    }
    pool.clear();
}

}  // namespace GLngin
