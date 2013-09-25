#include <ctime>
#include "BnD.hpp"
#include "Log.hpp"
#include "CoF.hpp"

int main(int argc, char** argv)
{
    /*/
    char logfile[BnD::FILENAME_MAX_LEN];
    std::time_t now = std::time(nullptr);
    std::strftime(logfile, BnD::FILENAME_MAX_LEN, "%Y-%m-%d_%H-%M-%S.log", std::localtime(&now));
    /**/
    Log::Init(Log::Level::Info/*, logfile*/);
    Log::Info("Initializing...");

    CoF::Init("Colosseum of Fate", 1600, 900);
    CoF::Loop();

    Log::Info("Quiting...");
    CoF::Quit();
    Log::Quit();
    return 0;
}

