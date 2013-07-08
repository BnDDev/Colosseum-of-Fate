#include "appmain.h"

void AppMain::Log(LogLevel ll, const char* fmt, ...)
{
    if(ll > debug) return;
    va_list args;
    va_start(args, fmt);
    std::chrono::steady_clock::duration telapsed = std::chrono::steady_clock::now() - tstart;
    switch(ll)
    {
        case LogLevel::EVER:
            fprintf(flog, " [EVER] %16llu | ", telapsed.count());
            vfprintf(flog, fmt, args);
            fprintf(flog, "\n");
            break;
        case LogLevel::INFO:
            fprintf(flog, " [INFO] %16llu | ", telapsed.count());
            vfprintf(flog, fmt, args);
            fprintf(flog, "\n");
            break;
        case LogLevel::WARN:
            fprintf(flog, " [WARN] %16llu | ", telapsed.count());
            vfprintf(flog, fmt, args);
            fprintf(flog, "\n");
            fflush(flog);
            break;
        case LogLevel::ERROR:
            fprintf(flog, "[ERROR] %16llu | ", telapsed.count());
            vfprintf(flog, fmt, args);
            fprintf(flog, "\n");
            fflush(flog);
            break;
        default:
            return;
    }
    va_end(args);
}

AppMain::AppMain(int argc, char** argv) : flog(nullptr)
{
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    tstart = std::chrono::steady_clock::now();
    debug = LogLevel::INFO;

    if(debug != LogLevel::NONE) {
        char filename[FILENAME_MAX_LEN];
        std::time_t now = std::time(nullptr);
        std::strftime(filename, FILENAME_MAX_LEN, "%Y-%m-%d_%H-%M-%S.log", std::localtime(&now));
        flog = fopen(filename, "w");
    }

    Log(LogLevel::INFO, "AppMain()");
}

AppMain::~AppMain()
{
    SDL_Delay(1000);
    Log(LogLevel::INFO, "~AppMain()");
    if(flog) fclose(flog);
}
