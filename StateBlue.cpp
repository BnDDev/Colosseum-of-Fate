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
    template<> bool StateTemplate<StateEnum::Blue>::Tick() {
        while(SDL_PollEvent(&global.event)) {
            switch(global.event.type)
            {
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
                global.state = StateEnum::Red;
                Quit();
                return false;
            case SDL_QUIT:
                global.state = StateEnum::QUIT;
                Quit();
                return false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        return true;
    }
}
