/*
#include <type_traits>
#include <iostream>

// Enable only if T is integral
template <typename T>
std::enable_if_t<std::is_integral_v<T>, void>
printType(const T&) {
    std::cout << "Integral type\n";
}

// Enable only if T is floating point
template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, void>
printType(const T&) {
    std::cout << "Floating point type\n";
}

int main() {
    printType(42);     // Integral type
    printType(3.14);   // Floating point type
}
*/

//-------------------------------------------------------------------------

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
