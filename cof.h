#ifndef COF_H
#define COF_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "log.h"
#include "bnd.h"

namespace CoF
{
    enum StateEnum : uint8_t {
        Red,
        Blue,
        length
    };
    struct State {
        StateEnum id;
        void* data;
        void (*Init)();
        void (*Quit)();
    };
    template<int I> class StateTemplate {
    public:
        static void Init();
        static void Quit();
    };
    template<typename> class StateMachineTemplate;
    template<int... I> class StateMachineTemplate<BnD::Indices<I...>> {
    public:
        static constexpr void (*Init[sizeof...(I)])() { (StateTemplate<I>::Init)... };
        static constexpr void (*Quit[sizeof...(I)])() { (StateTemplate<I>::Quit)... };
    };
    using StateMachine = StateMachineTemplate<BnD::ExpandIndices<StateEnum::length>>;


    namespace {
        SDL_Window* window;
        SDL_GLContext glcontext;
        State currentState;
    }
    bool Init(const char*, int, int);
    void Quit();
    void Loop();
}

#endif // COF_H
