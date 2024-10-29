#ifndef URCHIN_GRAPH_COMMAND
#define URCHIN_GRAPH_COMMAND

#include <unordered_set>

#include "command.h"
#include "../../core/timer.h"

namespace UrchinCLI {

class GraphCommand : public Command {
public:
  GraphCommand() {}
  GraphCommand(const std::string filePath) : _filePath(filePath) {} 

  void execute();

  void findDependencies(const std::string &filePath);

public:
  std::string _filePath;
  std::unordered_set<std::string> _visited;
  std::unordered_map<std::string, std::vector<std::string>> _dependencies;
};

}

#endif // URCHIN_GRAPH_COMMAND
