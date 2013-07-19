#include "cof.h"

namespace CoF {
    namespace {
        extern SDL_Window* window;
        extern SDL_GLContext glcontext;
    }

    template<int I> StateDataTemplate<I> StateTemplate<I>::data = StateDataTemplate<I>();

    ////////////////////////////////
    /// StateEnum::Red           ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Red>::Init() {
        Log::Info("State<Red>::Init()");
        glClearColor(1.0, 0.0, 0.0, 1.0);
    }
    template<> void StateTemplate<StateEnum::Red>::Quit() {
        Log::Info("State<Red>::Quit()");
    }
    template<> bool StateTemplate<StateEnum::Red>::Tick() {
        while(SDL_PollEvent(&data.event)) {
            switch(data.event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                state.current = StateEnum::Blue;
                Quit();
                return false;
            case SDL_QUIT:
                state.current = StateEnum::Global;
                Quit();
                return false;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        return true;
    }

    ////////////////////////////////
    /// StateEnum::Blue          ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Blue>::Init() {
        Log::Info("State<Blue>::Init()");
        glClearColor(0.0, 0.0, 1.0, 1.0);
    }
    template<> void StateTemplate<StateEnum::Blue>::Quit() {
        Log::Info("State<Blue>::Quit()");
    }
    template<> bool StateTemplate<StateEnum::Blue>::Tick() {
        while(SDL_PollEvent(&data.event)) {
            switch(data.event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                state.current = StateEnum::Red;
                Quit();
                return false;
            case SDL_QUIT:
                state.current = StateEnum::Global;
                Quit();
                return false;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        return true;
    }
    template<int... I> constexpr void (*StateMachineTemplate<BnD::Indices<I...>>::Init[sizeof...(I)])();
    template<int... I> constexpr void (*StateMachineTemplate<BnD::Indices<I...>>::Quit[sizeof...(I)])();
    template<int... I> constexpr bool (*StateMachineTemplate<BnD::Indices<I...>>::Tick[sizeof...(I)])();

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

        state.current = StateEnum::first;
        ChangeState();
    }
    bool ChangeState() {
        if(state.current >= StateEnum::length) return false;
        state.Init = StateMachine::Init[state.current];
        state.Tick = StateMachine::Tick[state.current];
        state.Quit = StateMachine::Quit[state.current];
        state.Init();
        return true;
    }
    void Quit() {
        Log::Info("CoF::Quit()");
        if(glcontext) SDL_GL_DeleteContext(glcontext);
        if(window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Loop() {
        while(state.Tick() || ChangeState()) SDL_GL_SwapWindow(window);
    }
}
