#ifndef GLAPP_H
#define GLAPP_H

#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "log.h"


enum StateID : uint8_t {
    Red,
    Blue,
    Null
};

struct StateData {
};

struct State {
    StateData* data;

    std::function<bool(StateData*)> update; // returns true to init next state
    std::function<void(StateData*)> redraw;
};

template<int ID> class AppState {
};

template<> class AppState<StateID::Red> {
public:
    static bool Init(StateID) {
        Log::Info("StateRed::Init!");
        return false;
    }
};

template<> class AppState<StateID::Blue> {
public:
    static bool Init(StateID) {
        Log::Info("StateBlue::Init!");
        return false;
    }
};

class StateMachine {
public:
    static constexpr bool (*StateInit[StateID::Null])(StateID) = {
            AppState<StateID::Red>::Init,
            AppState<StateID::Blue>::Init
    };
};

class GLApp {
public:
    GLApp(const char*, int, int);
    ~GLApp();
    bool tick();
protected:
private:
    SDL_Window* window;
    SDL_GLContext glcontext;
    State* state;
    bool InitState(StateID); // returns false to quit
};

#endif // GLAPP_H
