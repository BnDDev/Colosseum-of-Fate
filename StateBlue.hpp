#ifndef STATEBLUE_HPP
#define STATEBLUE_HPP

#include "CoF.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <array>
#include <vector>

namespace CoF {
    template<> struct StateDataTemplate<StateEnum::Blue> {
        static constexpr const GLchar* const vs =
            "#version 330 core\n"

            "uniform mat4 uMat4P;"
            "uniform mat4 uMat4V;"
            "uniform mat4 uMat4M;"
            "uniform vec3 uVec3Light;"
            "in vec3 iVec3Vertex;"
            "in vec3 iVec3Normal;"
            "out vec3 pVec3Normal;"
            "out vec3 pVec3Vertex;"
            "out vec3 pVec3Light;"

            "void main() {"
                "pVec3Normal = iVec3Normal;"
                "gl_Position = uMat4P * uMat4V * uMat4M * vec4(iVec3Vertex, 1.0);"
                "pVec3Vertex = vec3(gl_Position);"
                "pVec3Light = normalize(uVec3Light);"
            "}";

        static constexpr const GLchar* const fs =
            "#version 330 core\n"

            "in vec3 pVec3Light;"
            "in vec3 pVec3Normal;"
            "in vec3 pVec3Vertex;"
            "out vec4 oVec4Color;"

            "void main() {"
                //"float c = 1.0 - (pVec3Vertex.z + 1.0) / 2.0;"
                "float c = max(0.25, dot(pVec3Normal, pVec3Light));"
                "oVec4Color = vec4(c, c, c, 1.0);"
            "}";

        Mesh3D<BnD::Mesh::NORMALS> mesh;
        BnD::Mat<GLfloat> matV;
        BnD::Mat<GLfloat> matM;
        GLuint VAO;
        GLuint VBOVertex;
        GLuint VBOIndex;
        GLuint GLProgram;
        GLint iVec3Vertex;
        GLint iVec3Normal;
        GLint uMat4P;
        GLint uMat4V;
        GLint uMat4M;
        GLint uVec3Light;
        BnD::Vec<GLfloat, 2> rotation;
        BnD::Vec<GLfloat, 3> vecLight;
        uint32_t inputFlags;
        enum InputFlags {
            None = 0x0,
            ArrowUp = 0x1,
            ArrowDown = 0x2,
            ArrowLeft = 0x4,
            ArrowRight = 0x8,
            MouseLeft = 0x10,
            MouseRight = 0x20,
            MouseMiddle = 0x40
        };
    };
}

#endif // STATEBLUE_HPP
