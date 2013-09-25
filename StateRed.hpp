#ifndef STATERED_H
#define STATERED_H

#include "CoF.hpp"

namespace CoF {
    template<> struct StateDataTemplate<StateEnum::Red> {
        static constexpr size_t MAX_TARGETS = 5;
        static constexpr const GLchar* const vs =
                "#version 330 core\n"

                "uniform mat4 uMat4P;"
                "uniform mat4 uMat4MV;"
                "uniform float uFloatTime;"
                "in vec4 iVec4Data;"
                "out float pFloatRadius;"

                "void main() {"
                    "pFloatRadius = iVec4Data.w;"
                    "gl_Position = vec4(iVec4Data.xyz, 1.0);"
                "}";

        static constexpr const GLchar* const gs =
                "#version 330 core\n"

                "uniform mat4 uMat4P;"
                "uniform mat4 uMat4MV;"
                "layout(points) in;"
                "layout(triangle_strip, max_vertices = 4) out;"
                "in float pFloatRadius[1];"
                "out vec2 pVec2Tex;"
                "out float pFloatR;"

                "void main() {"

                    "if(pFloatRadius[0] > 0.0) {"
                        "pVec2Tex = vec2(0.0, 0.0);"
                        "pFloatR = pFloatRadius[0];"
                        "gl_Position = uMat4P * uMat4MV * vec4(gl_in[0].gl_Position.x - pFloatRadius[0], gl_in[0].gl_Position.y - pFloatRadius[0], gl_in[0].gl_Position.zw);"
                        "EmitVertex();"

                        "pVec2Tex = vec2(0.0, 1.0);"
                        "pFloatR = pFloatRadius[0];"
                        "gl_Position = uMat4P * uMat4MV * vec4(gl_in[0].gl_Position.x - pFloatRadius[0], gl_in[0].gl_Position.y + pFloatRadius[0], gl_in[0].gl_Position.zw);"
                        "EmitVertex();"

                        "pVec2Tex = vec2(1.0, 0.0);"
                        "pFloatR = pFloatRadius[0];"
                        "gl_Position = uMat4P * uMat4MV * vec4(gl_in[0].gl_Position.x + pFloatRadius[0], gl_in[0].gl_Position.y - pFloatRadius[0], gl_in[0].gl_Position.zw);"
                        "EmitVertex();"

                        "pVec2Tex = vec2(1.0, 1.0);"
                        "pFloatR = pFloatRadius[0];"
                        "gl_Position = uMat4P * uMat4MV * vec4(gl_in[0].gl_Position.x + pFloatRadius[0], gl_in[0].gl_Position.y + pFloatRadius[0], gl_in[0].gl_Position.zw);"
                        "EmitVertex();"
                    "}"

                    "EndPrimitive();"
                "}";

        static constexpr const GLchar* const fs =
                "#version 330 core\n"

                "#define M_PI 3.1415926535897932384626433832795\n"

                "uniform float uFloatTime;"
                "in vec2 pVec2Tex;"
                "in float pFloatR;"
                "out vec4 oVec4Color;"

                "void main() {"
                    "float dis = distance(vec2(0.5, 0.5), pVec2Tex);"
                    "float s = sin((dis * 2.0 - 1.0) * pFloatR / 100.0 * M_PI * 5.0);" // for pFloatR == 100.0 we get 5 rings
                    "float c = smoothstep(-0.2, 0.2, s);"
                    "float c2 = 1.0 - smoothstep(0.49, 0.5, dis);"
                    "oVec4Color = vec4(max(c, 0.5), c, max(c, 0.5), c2);"
                "}";

        std::chrono::steady_clock::time_point tstart, tlast;
        GLuint glp;
        GLuint vao;
        GLuint vbo;
        GLint iVec4Data;
        GLint uMat4P;
        GLint uMat4MV;
        GLint uFloatTime;
        struct {
            union {
                GLfloat data[4];
                struct {
                    Vec3 position;
                    GLfloat radius;
                };
            };
        } targets[MAX_TARGETS];
        GLfloat sv[MAX_TARGETS];
    };
}

#endif // STATERED_H
