#include <ctime>
#include "bnd.h"
#include "log.h"
#include "cof.h"

int main(int argc, char** argv)
{
    /*/
    char logfile[BnD::FILENAME_MAX_LEN];
    std::time_t now = std::time(nullptr);
    std::strftime(logfile, BnD::FILENAME_MAX_LEN, "%Y-%m-%d_%H-%M-%S.log", std::localtime(&now));
    /**/
    Log::Init(Log::Level::Info/*, logfile*/);
    Log::Info("Initializing...");

    CoF::Init("Colosseum of Fate", 800, 600);
    CoF::Loop();
    CoF::Quit();

    Log::Info("Quiting...");
    Log::Quit();
    return 0;
}

