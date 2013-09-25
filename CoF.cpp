#include "CoF.hpp"

template<class C, int MAX> void* BnD::MemoryPool<C, MAX>::unused[MAX];
template<class C, int MAX> size_t BnD::MemoryPool<C, MAX>::length;

namespace CoF {
    StateDataTemplate<StateEnum::Global> global;

    bool Init(const char* str, int w, int h) {
        Log::Info("CoF::Init(\"%s\", %d, %d)", str, w, h);

        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            Log::Error("SDL_Init failed: %s", SDL_GetError());
            return false;
        }
        Log::Info("SDL_Init OK");

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        global.window = SDL_CreateWindow(str, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
        if(!global.window) {
            Log::Error("SDL_CreateWindow failed: %s", SDL_GetError());
            return false;
        }
        Log::Info("SDL_CreateWindow OK");

        global.glcontext = SDL_GL_CreateContext(global.window);
        if(!global.glcontext) {
            Log::Error("SDL_GL_CreateContext failed: %s", SDL_GetError());
            return false;
        }
        Log::Info("SDL_GL_CreateContext OK");

        Log::Info("OpenGL context created with version: %s", glGetString(GL_VERSION));

        int ret;
        if((ret = LoadGLFunctions())) {
            Log::Error("loadGLFunctions failed: %d", ret);
            return false;
        }
        Log::Info("LoadGLFunctions OK");

        GLOrtho(global.matP, 0.0f, w, h, 0.0f, -1.0, 1.0f);
        GLIdentity(global.matMV);

        global.state = StateEnum::INIT;
        if(!InitState()) global.Tick = nullptr;

        return true;
    }
    bool InitState() {
        if(global.state >= StateEnum::length) return false;
        StateMachine::Init[global.state]();
        global.Tick = StateMachine::Tick[global.state];
        return true;
    }
    void SwitchState(StateEnum nextState) {
        StateMachine::Quit[global.state]();
        global.state = nextState;
        if(!InitState()) global.Tick = nullptr;
    }
    void Quit() {
        Log::Info("CoF::Quit()");
        if(global.glcontext) SDL_GL_DeleteContext(global.glcontext);
        if(global.window) SDL_DestroyWindow(global.window);
        SDL_Quit();
    }
    void Loop() {
        while(global.Tick) {
            global.Tick();
            SDL_GL_SwapWindow(global.window);
        }
    }
}
