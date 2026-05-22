#include <iostream>
#include <meta>
#include <string>
#include <string_view>
#include <type_traits>

struct MyClass {};

struct X {
  double foo(std::string, int);
  double foos;
};

int main() {
  constexpr auto ns_refl = ^^X;
  constexpr auto ctx = std::meta::access_context::unchecked();
  constexpr auto members =
      std::define_static_array(std::meta::members_of(ns_refl, ctx));
  template for (constexpr auto& member : auto(members)) {
    if constexpr (std::meta::has_identifier(member))
      std::cout << std::meta::identifier_of(member) << '\n';
  }
}