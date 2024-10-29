#ifndef URCHIN_COMMAND
#define URCHIN_COMMAND

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

namespace UrchinCLI {

class Command {
public:
  virtual ~Command() = default;
  virtual void execute() = 0;
};

class CommandParser {
public:
  CommandParser(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
      _args.push_back(argv[i]);
    }
  }

  std::unique_ptr<UrchinCLI::Command> findCommand();
private:
  std::vector<std::string> _args;
};

}

#endif // URCHIN_COMMAND
