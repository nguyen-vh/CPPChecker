#include <iostream>

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  typename[:^^char:] c = 'C';

  std::cout << c << "\n";

  std::cout << std::endl;
  return 0;
}