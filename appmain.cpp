#include "appmain.h"

void AppMain::Log(LogLevel ll, const char* str, size_t num = 0)
{
    if(ll > debug) return;
    std::chrono::steady_clock::duration telapsed = std::chrono::steady_clock::now() - tstart;
    switch(ll)
    {
        case LogLevel::EVER:
            olog<<" [EVER] "<<std::dec<<std::setw(16)<<std::setfill(' ')<<telapsed.count()<<" | "<<str;
            if(num) olog<<" (0x"<<std::hex<<std::setw(sizeof(num) * 2)<<std::setfill('0')<<std::uppercase<<num<<")";
            olog<<"\n";
            break;
        case LogLevel::INFO:
            olog<<" [INFO] "<<std::dec<<std::setw(16)<<std::setfill(' ')<<telapsed.count()<<" | "<<str;
            if(num) olog<<" (0x"<<std::hex<<std::setw(sizeof(num) * 2)<<std::setfill('0')<<std::uppercase<<num<<")";
            olog<<"\n";
            break;
        case LogLevel::WARN:
            olog<<" [WARN] "<<std::dec<<std::setw(16)<<std::setfill(' ')<<telapsed.count()<<" | "<<str;
            if(num) olog<<" (0x"<<std::hex<<std::setw(sizeof(num) * 2)<<std::setfill('0')<<std::uppercase<<num<<")";
            olog<<"\n";
            olog.flush();
            break;
        case LogLevel::ERROR:
            olog<<"[ERROR] "<<std::dec<<std::setw(16)<<std::setfill(' ')<<telapsed.count()<<" | "<<str;
            if(num) olog<<" (0x"<<std::hex<<std::setw(sizeof(num) * 2)<<std::setfill('0')<<std::uppercase<<num<<")";
            olog<<"\n";
            olog.flush();
            break;
        default:
            return;
    }
}

AppMain::AppMain(int argc, char** argv) : olog(std::clog.rdbuf())
{
    tstart = std::chrono::steady_clock::now();
    debug = LogLevel::INFO;

    char filename[FILENAME_MAX_LEN];
    std::time_t now = std::time(nullptr);
    std::strftime(filename, FILENAME_MAX_LEN - 4, "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    std::strcat(filename, ".log");
    flog.open(filename, std::ios::trunc);
    olog.rdbuf(flog.rdbuf());

    Log(LogLevel::INFO, "AppMain()");
}

AppMain::~AppMain()
{
    Log(LogLevel::INFO, "~AppMain()");
}
