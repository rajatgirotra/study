//: C05:Gromit.h
// The techno-dog. Has member functions
// with various numbers of arguments.
#include <iostream>
 
class Gromit {
  int arf;
  int totalBarks;
public:
  Gromit(int arf = 1) : arf(arf + 1), totalBarks(0) {}
  void speak(int) {
    for(int i = 0; i < arf; i++) {
      std::cout << "arf! ";
      ++totalBarks;
    }
    std::cout << std::endl;
  }
  char eat(float) const {
    std::cout << "chomp!" << std::endl;
    return 'z';
  }
  int sleep(char, double)  {
    std::cout << "zzz..." << std::endl;
    return 0;
  }
  void sit() const {
    std::cout << "Sitting..." << std::endl;
  }
}; ///:~

