#include "Debug.hpp"

#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilut.h>

#include <cstring>
#include <fstream>

namespace GLngin {

std::string GetGLInfoString()
{
    int majorVersion, minorVersion;
    char buf[256];
    constexpr char FormatString[] =
        "GL Vendor            : %s\n"
        "GL Renderer          : %s\n"
        "GL Version (string)  : %s\n"
        "GL Version (integer) : %d.%d\n"
        "GLSL Version         : %s\n";

    GL_CALL(glGetIntegerv(GL_MAJOR_VERSION, &majorVersion));
    GL_CALL(glGetIntegerv(GL_MINOR_VERSION, &minorVersion));

    GL_CALL(sprintf(buf, FormatString, glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION),
                    majorVersion, minorVersion, glGetString(GL_SHADING_LANGUAGE_VERSION)));

    return buf;
}

const char *GetGLEnumStr(unsigned int enumElem)
{
#define GLENUM(e) \
    case e: return #e
    switch (enumElem) {
        GLENUM(GL_NO_ERROR);
        GLENUM(GL_INVALID_ENUM);
        GLENUM(GL_INVALID_VALUE);
        GLENUM(GL_INVALID_OPERATION);
        GLENUM(GL_INVALID_FRAMEBUFFER_OPERATION);
        GLENUM(GL_OUT_OF_MEMORY);
        GLENUM(GL_STACK_UNDERFLOW);
        GLENUM(GL_STACK_OVERFLOW);
    }
#undef GLENUM

    return "UNKNOWN_ENUM";
}

const char *GetILEnumStr(unsigned int enumElem)
{
#define ILENUM(e) \
    case e: return #e
    switch (enumElem) {
        ILENUM(IL_NO_ERROR);
        ILENUM(IL_INVALID_ENUM);
        ILENUM(IL_OUT_OF_MEMORY);
        ILENUM(IL_FORMAT_NOT_SUPPORTED);
        ILENUM(IL_INTERNAL_ERROR);
        ILENUM(IL_INVALID_VALUE);
        ILENUM(IL_ILLEGAL_OPERATION);
        ILENUM(IL_ILLEGAL_FILE_VALUE);
        ILENUM(IL_INVALID_FILE_HEADER);
        ILENUM(IL_INVALID_PARAM);
        ILENUM(IL_COULD_NOT_OPEN_FILE);
        ILENUM(IL_INVALID_EXTENSION);
        ILENUM(IL_FILE_ALREADY_EXISTS);
        ILENUM(IL_OUT_FORMAT_SAME);
        ILENUM(IL_STACK_OVERFLOW);
        ILENUM(IL_STACK_UNDERFLOW);
        ILENUM(IL_INVALID_CONVERSION);
        ILENUM(IL_LIB_JPEG_ERROR);
        ILENUM(IL_LIB_PNG_ERROR);
        ILENUM(IL_UNKNOWN_ERROR);
        ILENUM(ILUT_NOT_SUPPORTED);
    }
#undef ILENUM

    return "UNKNOWN_ENUM";
}

std::string GetFolderName(const std::string &filePath)
{
    return filePath.substr(0, filePath.find_last_of("/\\")) + "/";
}

std::optional<std::string> GetFileContent(const std::string &fileName)
{
    std::string content;
    std::ifstream ifs{fileName};

    if (ifs && !ifs.bad()) {
        content = std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
        ifs.close();
    } else {
        LOG(std::string("Error occurred during the opening of \'") + std::string(fileName) + std::string("\'"));
        return std::nullopt;
    }

    return content;
}

}  // namespace GLngin
