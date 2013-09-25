#include "StateBlue.hpp"

namespace CoF {
    ////////////////////////////////
    /// StateEnum::Blue::Init()  ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Blue>::Init() {
        Log::Info("State<Blue>::Init()");
        glClearColor(0.0, 0.0, 1.0, 1.0);
    }

    ////////////////////////////////
    /// StateEnum::Blue::Quit()  ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Blue>::Quit() {
        Log::Info("State<Blue>::Quit()");
    }

    ////////////////////////////////
    /// StateEnum::Blue::Tick()  ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Blue>::Tick() {
        while(SDL_PollEvent(&global.event)) {
            switch(global.event.type)
            {
            case SDL_QUIT:
                SwitchState(StateEnum::QUIT);
                return;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
