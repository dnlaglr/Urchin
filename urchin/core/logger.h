#ifndef URCHIN_LOGGER
#define URCHIN_LOGGER

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace UrchinCore {

enum LogLevel { DEBUG, INFO, ERROR };

class Logger {
public:
  Logger() {
    _logDir = std::filesystem::path(std::getenv("HOME")) / ".local" / "share" / "urchin" / "logs";

    createLogFile();
    if (!_logFile.is_open()) { std::cerr << "[ERROR] Could not open log file." << std::endl; }
  }

  ~Logger() { _logFile.close(); }

  void logToFile(LogLevel level, const std::string& message) {

    std::ostringstream logEntry;
    logEntry << getTimestamp() << " " << levelToStr(level) << " " << message << std::endl;

    if (_logFile.is_open()) {
      _logFile << logEntry.str();
      _logFile.flush();
    }
  }

private:
  std::ofstream _logFile;
  std::filesystem::path _logDir;

  std::string levelToStr(LogLevel level) {
    switch (level) {
      case DEBUG:
        return "[DEBUG]";
      case ERROR:
        return "[ERROR]";
      case INFO:
        return "[INFO]";
      default:
        return "[UNKNOWN]";
    }
  }

  void createLogFile() {
    if (!std::filesystem::exists(_logDir)) {
      std::filesystem::create_directories(_logDir);
    }

    std::string fileName = getTimestamp() + "-urchin.txt";
    std::filesystem::path filePath = _logDir / fileName;

    _logFile.open(filePath, std::ios::app);
  }

  std::string getTimestamp() {
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
    std::tm localTime = *std::localtime(&currentTime_t);
    
    std::ostringstream timestamp;
    timestamp << (localTime.tm_year + 1900) << "-"
              << std::setw(2) << std::setfill('0') << (localTime.tm_mon + 1) << "-"
              << std::setw(2) << std::setfill('0') << localTime.tm_mday << "_"
              << std::setw(2) << std::setfill('0') << localTime.tm_hour << ":"
              << std::setw(2) << std::setfill('0') << localTime.tm_min << ":"
              << std::setw(2) << std::setfill('0') << localTime.tm_sec;

    return timestamp.str();
  }
};

}

#endif // URCHIN_LOGGER
