#ifndef COF_H
#define COF_H

#include <SDL2/SDL.h>
#include "Log.hpp"
#include "BnD.hpp"
#include "GLFunctions.hpp"

namespace CoF
{
    enum StateEnum : uint8_t {
        Red,
        Blue,
        length,
        Global = length,
        INIT = Red,
        QUIT = length
    };

    using Vec3 = BnD::Vec<GLfloat, 3>;
    using Mat4 = BnD::Mat<GLfloat, 4>;

    template<int I> struct StateDataTemplate {};
    template<> struct StateDataTemplate<StateEnum::Global> {
        SDL_Window* window;
        SDL_GLContext glcontext;
        SDL_Event event;

        StateEnum state;
        void (*Tick)();

        Mat4 matP;
        Mat4 matMV;
    };

    /* <magic type="dark"> */
    template<int I> class StateTemplate {
        using StateData = StateDataTemplate<I>;
    private:
        static StateData self;
    public:
        static void Init();
        static void Quit();
        static void Tick();
    };

    template<typename> struct StateMachineTemplate;
    template<int... I> struct StateMachineTemplate<BnD::Indices<I...>> {
        static constexpr void (*Init[sizeof...(I)])() { (StateTemplate<I>::Init)... };
        static constexpr void (*Quit[sizeof...(I)])() { (StateTemplate<I>::Quit)... };
        static constexpr void (*Tick[sizeof...(I)])() { (StateTemplate<I>::Tick)... };
    };
    using StateMachine = StateMachineTemplate<BnD::ExpandIndices<StateEnum::length>>;

    template<int I> StateDataTemplate<I> StateTemplate<I>::self = StateDataTemplate<I>();
    template<int... I> constexpr void (*StateMachineTemplate<BnD::Indices<I...>>::Init[sizeof...(I)])();
    template<int... I> constexpr void (*StateMachineTemplate<BnD::Indices<I...>>::Quit[sizeof...(I)])();
    template<int... I> constexpr void (*StateMachineTemplate<BnD::Indices<I...>>::Tick[sizeof...(I)])();
    /* </magic> */

    extern StateDataTemplate<StateEnum::Global> global;
    bool Init(const char*, int, int);
    bool InitState();
    void SwitchState(StateEnum);
    void Quit();
    void Loop();
}

#endif // COF_H
