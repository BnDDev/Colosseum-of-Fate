#include <ctime>
#include <SDL2/SDL.h>
#include "CommonDefines.h"
#include "log.h"
#include "glapp.h"

void Init() {
    char logfile[FILENAME_MAX_LEN];
    std::time_t now = std::time(nullptr);
    std::strftime(logfile, FILENAME_MAX_LEN, "%Y-%m-%d_%H-%M-%S.log", std::localtime(&now));
    Log::Init(Log::Level::Info);
    Log::Info("Init");

    if(SDL_Init(SDL_INIT_VIDEO) < 0) Log::Error("SDL_Init failed: %s", SDL_GetError());
    else Log::Info("SDL_Init OK");
}

void Quit() {
    Log::Info("Quit");
    SDL_Quit();
    Log::Quit();
}

int main(int argc, char** argv)
{
    Init();

    GLApp* mainApp = new GLApp("Colosseum of Fate", 800, 600);
    while(mainApp->tick());
    delete mainApp;

    Quit();
    return 0;
}

