#ifndef URCHIN_TIMER
#define URCHIN_TIMER

#include <iomanip>
#include <iostream>
#include <chrono>
#include <ratio>
#include <string>

namespace UrchinCore {

class Timer {
public:
  Timer(const std::string functionName) : _functionName(functionName), _startTime(std::chrono::high_resolution_clock::now()) {}

  void stop() {
    this->_endTime = std::chrono::high_resolution_clock::now();
    auto durationMS = std::chrono::duration<double, std::milli>(this->_endTime - this->_startTime);

    std::cout << std::fixed << std::setprecision(2);
    if (durationMS.count() >= 100) {
      auto durationSec = std::chrono::duration_cast<std::chrono::seconds>(this->_endTime - this->_startTime);
      std::cout << "[DEBUG] " << this->_functionName << " took " << durationSec.count() << " seconds to execute." << std::endl;
    } else {
      std::cout << "[DEBUG] " << this->_functionName << " took " << durationMS.count() << " milliseconds to execute." << std::endl;
    }
  }

private:
  const std::string _functionName;
  std::chrono::high_resolution_clock::time_point _startTime;
  std::chrono::high_resolution_clock::time_point _endTime;
};

}

#endif // URCHIN_TIMER
