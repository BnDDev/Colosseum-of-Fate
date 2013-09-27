#ifndef LOG_HPP
#define LOG_HPP

#include <cstdio>
#include <cstdint>
#include <chrono>
#include <cstdarg>
#include <cassert>

namespace Log {
    enum class Level : uint8_t {
        None = 0,
        Ever,
        Error,
        Warn,
        Info
    };
    void Init(Level, const char* _default_ = nullptr);
    void Quit();
    void Ever(const char*, ...);
    void Info(const char*, ...);
    void Warn(const char*, ...);
    void Error(const char*, ...);

    namespace {
        FILE* flog = nullptr;
        Level debugLevel = Level::None;
        std::chrono::steady_clock::time_point tstart;
    }
}

#endif // LOG_HPP
