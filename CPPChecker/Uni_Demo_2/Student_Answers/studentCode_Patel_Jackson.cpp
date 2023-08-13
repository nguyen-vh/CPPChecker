#include <iostream>

using namespace std;

class MyClassX {
 public:
  int IDE;
  void printed() { cout << "Printed..." << endl; }
};

class MyClassY {
 public:
};

class MyClassZ {
 public:
  void OHM() {}
  double AMP;
  float VOLT;
};

int Schokolade{12};

int SomeFunctionX() { return 0; }

std::string Snake;

int main() {
  MyClassX x;
  x.printed();
  return 0;
}
