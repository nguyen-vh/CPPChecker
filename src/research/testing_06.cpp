#include <iostream>
#include <type_traits>

int hello(double, float, long long int);
int bye(float, long long int, double);

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout
      << (std::is_invocable_v<decltype(hello), long long int, double, float>)
      << std::endl;
  std::cout
      << (std::is_invocable_v<decltype(bye), long long int, double, float>)
      << std::endl;
  return 0;
}