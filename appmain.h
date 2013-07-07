#ifndef APPMAIN_H
#define APPMAIN_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <chrono>

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
    std::ofstream flog;
    std::ostream olog;
    std::chrono::steady_clock::time_point tstart;

protected:
    void Log(LogLevel, const char*, size_t);
public:
    AppMain(int, char**);
    ~AppMain();
};

#endif // APPMAIN_H
