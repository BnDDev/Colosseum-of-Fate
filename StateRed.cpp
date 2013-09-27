//#include "StateRed.hpp"
/*
namespace CoF {
    extern const GLchar* const StateDataTemplate<StateEnum::Red>::vs;
    extern const GLchar* const StateDataTemplate<StateEnum::Red>::gs;
    extern const GLchar* const StateDataTemplate<StateEnum::Red>::fs;

    ////////////////////////////////
    /// StateRed::Init()         ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Red>::Init() {
        Log::Info("StateRed::Init()");
        self.tstart = std::chrono::steady_clock::now();
        self.tlast = self.tstart;

        //const GLchar* vs = "#version 330 core\nuniform mat4 uMat4MVP; in vec4 iVec4Pos; in vec2 iVec2Tex; out vec2 pVec2Tex; void main(){ gl_Position = uMat4MVP * iVec4Pos; pVec2Tex = iVec2Tex; }";
        //const GLchar* fs = "#version 330 core\nuniform sampler2D uSampler2D; in vec2 pVec2Tex; out vec4 oColor; void main(){ oColor = texture(uSampler2D, pVec2Tex); }";

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        self.glp = NewGLProgram(self.vs, self.fs, self.gs);
        glUseProgram(self.glp);
        self.iVec4Data = glGetAttribLocation(self.glp, "iVec4Data");
        self.uMat4P = glGetUniformLocation(self.glp, "uMat4P");
        self.uMat4V = glGetUniformLocation(self.glp, "uMat4V");
        self.uMat4M = glGetUniformLocation(self.glp, "uMat4M");
        self.uFloatTime = glGetUniformLocation(self.glp, "uFloatTime");

        self.matV.Identity();
        self.matM.Identity();

        glUniformMatrix4fv(self.uMat4P, 1, GL_FALSE, global.matP());
        glUniformMatrix4fv(self.uMat4V, 1, GL_FALSE, self.matV());
        glUniformMatrix4fv(self.uMat4M, 1, GL_FALSE, self.matM());

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

        glClearColor(1.0, 0.0, 0.0, 1.0);
    }

    ////////////////////////////////
    /// StateRed::Quit()         ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Red>::Quit() {
        Log::Info("StateRed::Quit()");

        glDeleteBuffers(1, &self.vbo);
        glDeleteVertexArrays(1, &self.vao);
        glDeleteProgram(self.glp);
    }

    ////////////////////////////////
    /// StateRed::Tick()         ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Red>::Tick() {
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
                SwitchState(StateEnum::QUIT);
                return;
            }
        }
    }
}*/
