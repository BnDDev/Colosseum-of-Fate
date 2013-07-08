#ifndef APPMAIN_H
#define APPMAIN_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <chrono>
#include <SDL2/SDL.h>

#define FILENAME_MAX_LEN 256

class AppMain {
private:
    enum class LogLevel : uint8_t {
        NONE = 0,
        EVER,
        ERROR,
        WARN,
        INFO
    } debug;
    FILE* flog;
    std::chrono::steady_clock::time_point tstart;

protected:
    void Log(LogLevel, const char*, ...);
public:
    AppMain(int, char**);
    ~AppMain();
};

#endif // APPMAIN_H
