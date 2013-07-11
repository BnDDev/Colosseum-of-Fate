#include "glapp.h"

GLApp::GLApp(const char* str, int w, int h) {
    Log::Info("GLApp(\"%s\", %d, %d)", str, w, h);
    tlast = std::chrono::steady_clock::now();
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
    std::chrono::steady_clock::time_point tnow = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration telapsed = tlast - tnow;
    tlast = tnow;

    //handleEvents();
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) return false;
    }
    //update();
    //redraw();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    return true;
}
