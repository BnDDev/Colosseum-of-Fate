#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>

#include "appmain.h"

void error(const char* msg)
{
    std::cout<<msg<<std::endl;
    SDL_Quit();
    exit(1);
}

void loop(SDL_Window* window)
{
    SDL_Event event;
    while(true)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEMOTION:
                {
                    break;
                }
                case SDL_QUIT: return;
                default: break;
            }
        }
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
        SDL_Delay(10);
    }
}

int main(int argc, char** argv)
{
    AppMain(argc, argv);
    if(SDL_Init(SDL_INIT_VIDEO) < 0) error("Error initializing SDL with Video");

    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window* window = SDL_CreateWindow("Colosseum of Fate", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!window) error("Could not create SDL window");

    SDL_Surface* surface = IMG_Load("icon2.png");
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);

    SDL_GLContext glcontext  = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;

    loop(window);

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

