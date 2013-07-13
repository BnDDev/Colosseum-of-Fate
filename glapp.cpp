#include "glapp.h"

extern bool constexpr (*StateMachine::StateInit[StateID::Null])(StateID);

GLApp::GLApp(const char* str, int w, int h) {
    Log::Info("GLApp(\"%s\", %d, %d)", str, w, h);
    window = SDL_CreateWindow(str, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
    if(!window) Log::Error("SDL_CreateWindow failed: %s", SDL_GetError());
    else {
        Log::Info("SDL_CreateWindow OK");
        glcontext = SDL_GL_CreateContext(window);
        if(!glcontext) Log::Error("SDL_GL_CreateContext failed: %s", SDL_GetError());
        else {
            Log::Info("SDL_GL_CreateContext OK");
            Log::Info("OpenGL context created with version: %s", glGetString(GL_VERSION));
        }
    }
}

GLApp::~GLApp() {
    Log::Info("~GLApp()");
    if(glcontext) SDL_GL_DeleteContext(glcontext);
    if(window) SDL_DestroyWindow(window);
}

bool GLApp::tick() {
    //if(state->update(state->data) && !InitState(state->data->nextState)) return false;
    //state->redraw(state->data);
    //SDL_GL_SwapWindow(window);

    StateMachine::StateInit[StateID::Red](StateID::Red);
    return true;
}

bool GLApp::InitState(StateID nextState) {
    return true;
}
