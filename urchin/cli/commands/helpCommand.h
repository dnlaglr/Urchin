#ifndef URCHIN_HELP_COMMAND
#define URCHIN_HELP_COMMAND

#include <chrono>

#include "command.h"
#include "../../core/timer.h"

namespace UrchinCLI {

class HelpCommand : public Command {
public:
  void execute() override {
  #ifdef URCHIN_DEBUG
    std::cout << "[DEBUG] Running help command." << std::endl;
    UrchinCore::Timer cmdTimer("Help Command");
  #endif // URCHIN_DEBUG

    std::cout << "\nUrchin - C++ Dependency Grapher\n\n"
      << "help - Gives general help information about all available commands\n"
      << "graph - Graphs dependencies from program entry file\n"
      << "graph <path> - Graphs dependencies relative to specified file\n"
      << "[command] help - Gives detailed information about a specific command\n" <<
    std::endl;
  
  #ifdef URCHIN_DEBUG
    cmdTimer.stop();
  #endif // URCHIN_DEBUG
  }
};

}

#endif // URCHIN_HELP_COMMAND
