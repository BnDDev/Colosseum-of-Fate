#ifndef COF_HPP
#define COF_HPP

#include <SDL2/SDL.h>
#include "Log.hpp"
#include "BnD.hpp"
#include "GLFunctions.hpp"

namespace CoF
{
    enum StateEnum : uint8_t {
        //Red,
        Blue,
        length,
        Global = length,
        INIT = Blue,
        QUIT = length
    };

    template<uint8_t F> using Mesh3D = BnD::Mesh::GenericMesh<GLfloat, GLuint, 3, 3, F>;

    template<int I> struct StateDataTemplate {};
    template<> struct StateDataTemplate<StateEnum::Global> {
        SDL_Window* window;
        SDL_GLContext glcontext;
        SDL_Event event;

        StateEnum state;
        void (*Tick)();

        BnD::Mat<GLfloat> matP;
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

#endif // COF_HPP
