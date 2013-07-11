#ifndef GLAPP_H
#define GLAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "log.h"

class GLApp {
public:
    GLApp(const char*, int, int);
    ~GLApp();
    bool tick();
protected:
private:
    SDL_Window* window;
    SDL_GLContext glcontext;
    std::chrono::steady_clock::time_point tlast;
};

#endif // GLAPP_H
