#include "cof.h"

namespace CoF {
    namespace {
        extern SDL_Window* window;
        extern SDL_GLContext glcontext;
    }

    template<> void StateTemplate<StateEnum::Red>::Init() { Log::Info("State<Red>::Init()"); }
    template<> void StateTemplate<StateEnum::Red>::Quit() { Log::Info("State<Red>::Quit()"); }
    template<> void StateTemplate<StateEnum::Blue>::Init() { Log::Info("State<Blue>::Init()"); }
    template<> void StateTemplate<StateEnum::Blue>::Quit() { Log::Info("State<Blue>::Quit()"); }
    template<int... I> constexpr void (*StateMachineTemplate<BnD::Indices<I...>>::Init[sizeof...(I)])();
    template<int... I> constexpr void (*StateMachineTemplate<BnD::Indices<I...>>::Quit[sizeof...(I)])();

    bool Init(const char* str, int w, int h) {
        Log::Info("CoF::Init(\"%s\", %d, %d)", str, w, h);

        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            Log::Error("SDL_Init failed: %s", SDL_GetError());
            return false;
        }
        Log::Info("SDL_Init OK");

        window = SDL_CreateWindow(str, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
        if(!window) {
            Log::Error("SDL_CreateWindow failed: %s", SDL_GetError());
            return false;
        }
        Log::Info("SDL_CreateWindow OK");

        glcontext = SDL_GL_CreateContext(window);
        if(!glcontext) {
            Log::Error("SDL_GL_CreateContext failed: %s", SDL_GetError());
            return false;
        }
        Log::Info("SDL_GL_CreateContext OK");

        Log::Info("OpenGL context created with version: %s", glGetString(GL_VERSION));
    }

    void Quit() {
        Log::Info("CoF::Quit()");
        if(glcontext) SDL_GL_DeleteContext(glcontext);
        if(window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Loop() {
        /**/
        for(uint8_t i = 0; i < StateEnum::length; i++) {
            StateMachine::Init[i]();
            StateMachine::Quit[i]();
        }
        /*/
        while(true) {
            if(state->update(state->data) && !InitState(state->data->nextState)) return false;
            state->redraw(state->data);
            SDL_GL_SwapWindow(window);
        }
        /**/
    }
}
