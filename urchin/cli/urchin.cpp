#include <iostream>

#include "commands/command.h"

int main(int argc, char* argv[]) {
#ifdef URCHIN_DEBUG
  std::cout << "[DEBUG] Urchin CLI called with " << argc << " arguments: [";
  for (int i = 0; i < argc; i++) {
    if (i == argc - 1) {
      std::cout << argv[i];
    } else if (i < argc - 1) {
      std::cout << argv[i] << ", ";    
    }
  }
  std::cout << "]" << std::endl;
#endif

  if (argc < 2) {
    std::cerr << "[ERROR] Please specify a command." << std::endl;
    return 1;
  }

  UrchinCLI::CommandParser parser(argc, argv);
  auto command = parser.findCommand();

  if (command) {
    command->execute();
  } else {
    std::cerr << "[ERROR] " << argv[1] << " is not a recognized command." << std::endl;
    return 1;
  }

  return 0;

}
