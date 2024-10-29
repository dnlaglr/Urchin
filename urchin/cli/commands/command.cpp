#include <fstream>
#include <functional>
#include <filesystem>
#include <memory>
#include <algorithm>

#include "command.h"
#include "helpCommand.h"
#include "graphCommand.h"

std::unique_ptr<UrchinCLI::Command> UrchinCLI::CommandParser::findCommand() {
  static std::unordered_map<std::string, std::function<std::unique_ptr<UrchinCLI::Command>()>> commandMap = {
    {"help", []() { return std::make_unique<UrchinCLI::HelpCommand>(); }},
    {"graph", [this]() { 
      if (_args.size() < 2) {
      #ifdef URCHIN_DEBUG
        std::cout << "[DEBUG] Registering graph command with no file path." << std::endl;
      #endif
        return std::make_unique<UrchinCLI::GraphCommand>();
      }

      return std::make_unique<UrchinCLI::GraphCommand>(_args[1]); 
    }}
  };

  if (commandMap.find(_args[0]) != commandMap.end()) {
  #ifdef URCHIN_DEBUG
    std::cout << "[DEBUG] " << _args[0] << " command has been found and registered." << std::endl;
  #endif // URCHIN_DEBUG
    return commandMap[_args[0]]();
  }

  #ifdef URCHIN_DEBUG
    std::cout << "[DEBUG] " << _args[0] << " command was not found in command map. Returning nullptr." << std::endl;
  #endif // URCHIN_DEBUG

  return nullptr;
}

void UrchinCLI::GraphCommand::execute() {
#ifdef URCHIN_DEBUG
  std::cout << "[DEBUG] Running graph command." << std::endl;
  UrchinCore::Timer cmdTimer("Graph Command");
#endif // URCHIN_DEBUG

  findDependencies(_filePath);

  std::cout << "[\n";
  for (const auto &entry : _dependencies) {
    std::cout << "  { \"" << entry.first << "\": [";
    for (size_t i = 0; i < entry.second.size(); i++) {
      std::cout << "\"" << entry.second[i] << "\"";
      if (i < entry.second.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "] },\n";
  }
  std::cout << "]" << std::endl;

#ifdef URCHIN_DEBUG
  cmdTimer.stop();
#endif // URCHIN_DEBUG
}

void UrchinCLI::GraphCommand::findDependencies(const std::string &filePath) {
  if (_visited.find(filePath) != _visited.end()) {
    return;
  }

  _visited.insert(filePath);
  std::ifstream file(filePath);
  if (!file) {
    std::cerr << "[ERROR] Could not open " << filePath << "." << std::endl; 
    return;
  }

  std::string line;
  while (getline(file, line)) {
    size_t pos = line.find("#include");
    if (pos != std::string::npos) {
    #ifdef URCHIN_DEBUG
      std::cout << "[DEBUG] Found line: " << line << "." << std::endl;
    #endif // URCHIN_DEBUG
      size_t start = line.find("\"", pos);
      size_t end = line.find("\"", pos + 1);
      
      std::string includedFile;
      if (start != std::string::npos && end != std::string::npos) {
        includedFile = line.substr(start + 1, end - start - 1);
        includedFile.erase(std::remove(includedFile.begin(), includedFile.end(), '\"'), includedFile.end());
        #ifdef URCHIN_DEBUG
          std::cout << "[DEBUG] Found file: " << includedFile << "." << std::endl;
        #endif // URCHIN_DEBUG
      } else {
        start = line.find("<", pos);
        end = line.find(">", pos);
        
        if (start != std::string::npos && end != std::string::npos) {
          includedFile = line.substr(start + 1, end - start - 1);
        }
      }

      if (!includedFile.empty()) {
        std::filesystem::path includedFilePath = std::filesystem::path(filePath).parent_path() / includedFile;

        bool isStandardHeader = (line[start] == '<');

        _dependencies[std::filesystem::path(filePath).filename().string()].push_back(includedFile);

        if (!isStandardHeader && std::filesystem::exists(includedFilePath)) {
          findDependencies(includedFilePath);
        } else if (isStandardHeader) {
        #ifdef URCHIN_DEBUG
          std::cout << "[DEBUG] Skipping recursive search for standard header: " << includedFile << std::endl;
        #endif // URCHIN_DEBUG
        } else {
          std::cerr << "[ERROR] Included file " << includedFilePath << " does not exist." << std::endl;
        }
      }
    }
  }
}
