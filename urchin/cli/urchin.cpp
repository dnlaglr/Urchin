#include <iostream>

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
}
