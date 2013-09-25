#include "Log.hpp"

void Log::Init(Level ll, const char* file) {
    tstart = std::chrono::steady_clock::now();
    if(debugLevel == Level::None && ll != Level::None) {
        debugLevel = ll;
        if(file) flog = fopen(file, "w");
        else flog = stderr;
    }
}

void Log::Quit() {
    if(debugLevel != Level::None) {
        debugLevel = Level::None;
        if(flog != stderr) fclose(flog);
        flog = nullptr;
    }
}

void Log::Ever(const char* fmt, ...) {
    if(debugLevel < Level::Ever) return;
    std::chrono::steady_clock::duration telapsed = std::chrono::steady_clock::now() - tstart;
    va_list args;
    va_start(args, fmt);
    fprintf(flog, " [EVER] %16llu | ", telapsed.count());
    vfprintf(flog, fmt, args);
    fprintf(flog, "\n");
    fflush(flog);
    va_end(args);
}

void Log::Info(const char* fmt, ...) {
    if(debugLevel < Level::Info) return;
    std::chrono::steady_clock::duration telapsed = std::chrono::steady_clock::now() - tstart;
    va_list args;
    va_start(args, fmt);
    fprintf(flog, " [INFO] %16llu | ", telapsed.count());
    vfprintf(flog, fmt, args);
    fprintf(flog, "\n");
    fflush(flog);
    va_end(args);
}

void Log::Warn(const char* fmt, ...) {
    if(debugLevel < Level::Warn) return;
    std::chrono::steady_clock::duration telapsed = std::chrono::steady_clock::now() - tstart;
    va_list args;
    va_start(args, fmt);
    fprintf(flog, " [WARN] %16llu | ", telapsed.count());
    vfprintf(flog, fmt, args);
    fprintf(flog, "\n");
    fflush(flog);
    va_end(args);
}

void Log::Error(const char* fmt, ...) {
    if(debugLevel < Level::Error) return;
    std::chrono::steady_clock::duration telapsed = std::chrono::steady_clock::now() - tstart;
    va_list args;
    va_start(args, fmt);
    fprintf(flog, "[ERROR] %16llu | ", telapsed.count());
    vfprintf(flog, fmt, args);
    fprintf(flog, "\n");
    fflush(flog);
    va_end(args);
}
