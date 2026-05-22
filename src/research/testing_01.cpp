#include <concepts>
#include <iostream>

template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept Floating = std::is_floating_point_v<T>;

void printType(Integral auto) { std::cout << "Integral type\n"; }

void printType(Floating auto) { std::cout << "Floating point type\n"; }

int main() {
  printType(42);
  printType(3.14);
}
