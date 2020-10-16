#include "ShaderSamples.hpp"

namespace GLngin {

const char *const TransformVS = R"(
    #version 430

    // data from the input assembler
    in vec3 mPos;
    in vec3 mNorm;
    in vec2 tex;

    // global constant variables for all the vertices
    uniform mat4 M;
    uniform mat4 Minv;
    uniform mat4 MVP;

    // output variables
    out vec3 wPos;
    out vec3 wNorm;
    out vec2 tPos;

    void main()
    {
        wPos = (vec4(mPos, 1.0) * M).xyz;
        gl_Position = vec4(mPos, 1.0) * MVP;
        wNorm = (Minv * vec4(mNorm, 0.0)).xyz;
        tPos = tex;
    }
)";

const char *const BackgroundVS = R"(
    #version 430

    in vec3 mPos;
    
    uniform mat4 MVP;

    out vec3 tPos;

    void main()
    {
        gl_Position = vec4(mPos, 1.0) * MVP;
        tPos = mPos;
    }
)";

const char *const PhongBlinnFS = R"(
    #version 430

    // interpolated vertex data
    in vec3 wPos;
    in vec3 wNorm;
    in vec2 tPos;

    // global constant variables for all the fragments
    uniform sampler2D kd;
    uniform vec4 eyePos;
    uniform vec4 lightPos;
    uniform vec4 lightPowerDensity;

    // output parameter
    out vec4 outColor;

    void main()
    {
        vec4 ks = vec4(1.0, 1.0, 1.0, 64.0);
        vec4 ka = vec4(0.01, 0.01, 0.01, 1.0);

        vec3 n = normalize(wNorm);

        vec3 lightDir = normalize(lightPos.xyz - wPos);
        float cosTheta = dot(n, lightDir);

        if (cosTheta < 0.0) {
            outColor = ka;
            return;
        }

        vec3 viewDir = normalize(eyePos.xyz - wPos);
        vec3 halfway = normalize(viewDir + lightDir);
        float cosDelta = dot(n, halfway);

        if (cosDelta < 0.0) {
            outColor = ka;
            return;
        }

        vec4 md = texture2D(kd, tPos) * lightPowerDensity * cosTheta;
        vec4 ms = lightPowerDensity * ks * pow(cosDelta, ks.w);

        outColor = ka + md + ms;
    }
)";

const char *const SmoothFS = R"(
    #version 430

    in vec3 wPos;
    in vec3 wNorm;
    //in vec2 tPos;

    uniform samplerCube skybox;
    uniform vec3 eyePos;
    uniform vec3 idxOfRefr;
    uniform vec3 absorptCoeff;

    out vec4 outColor;

    const vec3 white = vec3(1.0, 1.0, 1.0);

    vec3 Reflectance(vec3 norm, vec3 toEye)
    {
        float cosa = abs(dot(norm, toEye));
        vec3 absorptCoeffSq = absorptCoeff * absorptCoeff;
        vec3 num = (idxOfRefr - white) * (idxOfRefr - white) + 4.0 * idxOfRefr * pow(1.0 - cosa, 5.0) + absorptCoeffSq;
        vec3 den = (idxOfRefr + white) * (idxOfRefr + white) + absorptCoeffSq;
        return num / den;
    }

    void main()
    {
        vec3 rayDir = normalize(wPos - eyePos);
        vec3 norm = normalize(wNorm);
        vec3 R = Reflectance(norm, -rayDir);

        vec4 redRefraction = (1.0 - R.r) * texture(skybox, refract(rayDir, norm, 1.0 / idxOfRefr.r));
        vec4 greenRefraction = (1.0 - R.g) * texture(skybox, refract(rayDir, norm, 1.0 / idxOfRefr.g));
        vec4 blueRefraction = (1.0 - R.b) * texture(skybox, refract(rayDir, norm, 1.0 / idxOfRefr.b));

        outColor = vec4(R, 1.0) * texture(skybox, reflect(rayDir, norm)) + (redRefraction + greenRefraction + blueRefraction) / 3.0;
    }
)";

const char *const MatCapFS = R"(
    #version 430

    //in vec3 wPos;
    in vec3 wNorm;
    //in vec2 tPos;

    uniform sampler2D kd;
    uniform mat4 V;

    out vec4 outColor;

    void main()
    {
        vec4 cNorm = vec4(normalize(wNorm), 0.0) * V;
        outColor = texture2D(kd, 0.5 * cNorm.xy + vec2(0.5, 0.5));
    }
)";

const char *const EnvMapFS = R"(
    #version 430

    in vec3 wPos;
    in vec3 wNorm;
    in vec2 tPos;
    
    uniform sampler2D kd;
    uniform samplerCube skybox;
    uniform vec4 eyePos;

    out vec4 outColor;

    void main()
    {
        vec3 reflDir = reflect(normalize(wPos - eyePos.xyz), normalize(wNorm));
        float w = 0.7;  // TODO uniform?

        outColor = w * texture(skybox, reflDir) + (1.0 - w) * texture2D(kd, tPos);
    }
)";

const char *const BackgroundFS = R"(
    #version 430

    in vec3 tPos;

    uniform samplerCube skybox;

    out vec4 outColor;

    void main()
    {
        outColor = texture(skybox, tPos);
    }
)";

}  // namespace GLngin
