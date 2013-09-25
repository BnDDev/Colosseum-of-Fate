#include "StateRed.hpp"

namespace CoF {
    ////////////////////////////////
    /// StateEnum::Red::Init()   ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Red>::Init() {
        Log::Info("State<Red>::Init()");
        self.tstart = std::chrono::steady_clock::now();
        self.tlast = self.tstart;

        //const GLchar* vs = "#version 330 core\nuniform mat4 uMat4MVP; in vec4 iVec4Pos; in vec2 iVec2Tex; out vec2 pVec2Tex; void main(){ gl_Position = uMat4MVP * iVec4Pos; pVec2Tex = iVec2Tex; }";
        //const GLchar* fs = "#version 330 core\nuniform sampler2D uSampler2D; in vec2 pVec2Tex; out vec4 oColor; void main(){ oColor = texture(uSampler2D, pVec2Tex); }";
        const GLchar* const vs =
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

        const GLchar* const gs =
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

        const GLchar* const fs =
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


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        self.glp = NewGLProgram(vs, fs, gs);
        glUseProgram(self.glp);
        self.iVec4Data = glGetAttribLocation(self.glp, "iVec4Data");
        self.uMat4P = glGetUniformLocation(self.glp, "uMat4P");
        self.uMat4MV = glGetUniformLocation(self.glp, "uMat4MV");
        self.uFloatTime = glGetUniformLocation(self.glp, "uFloatTime");

        glUniformMatrix4fv(self.uMat4P, 1, GL_FALSE, *global.matP.v);
        glUniformMatrix4fv(self.uMat4MV, 1, GL_FALSE, *global.matMV.v);

        glGenVertexArrays(1, &self.vao);
        glBindVertexArray(self.vao);
        glGenBuffers(1, &self.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, self.vbo);
        for(size_t i = StateData::MAX_TARGETS; i--;)
        {
            self.targets[i].position = {200.0f + i * 300.0f, 400.0f, 0.0f};
            self.targets[i].radius = 10.0f;
            self.sv[i] = 200.0f;
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(self.targets), self.targets, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(self.iVec4Data);
        glVertexAttribPointer(self.iVec4Data, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glClearColor(0.0, 0.0, 0.0, 1.0);
    }

    ////////////////////////////////
    /// StateEnum::Red::Quit()   ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Red>::Quit() {
        Log::Info("State<Red>::Quit()");

        glDeleteBuffers(1, &self.vbo);
        glDeleteVertexArrays(1, &self.vao);
        glDeleteProgram(self.glp);
    }

    ////////////////////////////////
    /// StateEnum::Red::Tick()   ///
    ////////////////////////////////
    template<> bool StateTemplate<StateEnum::Red>::Tick() {
        std::chrono::steady_clock::time_point tnow = std::chrono::steady_clock::now();
        std::chrono::steady_clock::duration tdiff = tnow - self.tlast;
        self.tlast = tnow;
        double dt = tdiff.count() / 1000000.0;

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(self.glp);
        glBindVertexArray(self.vao);
        for(size_t i = StateData::MAX_TARGETS; i--;)
        {
            self.targets[i].position = {200.0f + i * 300.0f, 400.0f, 0.0f};
            self.targets[i].radius += self.sv[i] * dt;
            if(self.targets[i].radius < 0.0f) {
                self.targets[i].radius = -1.0f;
                //self.sv[i] = 200.0f;
                SDL_ShowCursor(0);
            } else if(self.targets[i].radius > 100.0f) {
                self.targets[i].radius = 100.0f;
                self.sv[i] = 0.0f;
            }
        }

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(self.targets), self.targets);
        glDrawArrays(GL_POINTS, 0, StateData::MAX_TARGETS);

        while(SDL_PollEvent(&global.event)) {
            switch(global.event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                for(size_t i = StateData::MAX_TARGETS; i--;) {
                    GLfloat dx = global.event.button.x - self.targets[i].position.x;
                    GLfloat dy = global.event.button.y - self.targets[i].position.y;
                    if(dx * dx + dy * dy < self.targets[i].radius * self.targets[i].radius) {
                        self.sv[i] = -400.0f;
                        SDL_ShowCursor(1);
                    }
                }
                break;
            case SDL_QUIT:
                global.state = StateEnum::QUIT;
                Quit();
                return false;
            }
        }
        return true;
    }
}
