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
        length,
        Global = length,
        first = Red
    };

    template<int I> struct StateDataTemplate {};
    template<> struct StateDataTemplate<StateEnum::Red> {
        SDL_Event event;
    };
    template<> struct StateDataTemplate<StateEnum::Blue> {
        SDL_Event event;
    };
    template<> struct StateDataTemplate<StateEnum::Global> {
        StateEnum current;
        void (*Init)();
        void (*Quit)();
        bool (*Tick)();
    };

    template<int I> class StateTemplate {
    private:
        static StateDataTemplate<I> data;
    public:
        static void Init();
        static void Quit();
        static bool Tick();
    };

    template<typename> struct StateMachineTemplate;
    template<int... I> struct StateMachineTemplate<BnD::Indices<I...>> {
        static constexpr void (*Init[sizeof...(I)])() { (StateTemplate<I>::Init)... };
        static constexpr bool (*Tick[sizeof...(I)])() { (StateTemplate<I>::Tick)... };
        static constexpr void (*Quit[sizeof...(I)])() { (StateTemplate<I>::Quit)... };
    };
    using StateMachine = StateMachineTemplate<BnD::ExpandIndices<StateEnum::length>>;


    namespace {
        SDL_Window* window;
        SDL_GLContext glcontext;
        StateDataTemplate<StateEnum::Global> state;
    }
    bool Init(const char*, int, int);
    bool ChangeState();
    void Quit();
    void Loop();
}

#endif // COF_H
