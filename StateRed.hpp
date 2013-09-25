#ifndef STATERED_H
#define STATERED_H

#include "CoF.hpp"

namespace CoF {
    template<> struct StateDataTemplate<StateEnum::Red> {
        static constexpr size_t MAX_TARGETS = 5;
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
