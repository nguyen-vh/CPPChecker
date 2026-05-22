// Source - https://stackoverflow.com/a/79939812
// Posted by Artyer, modified by community. See post 'Timeline' for change
// history Retrieved 2026-05-14, License - CC BY-SA 4.0

#include <iostream>
#include <meta>

struct MyClass {};

int main() {
  constexpr auto ns_refl = ^^std;
  constexpr auto ctx = std::meta::access_context::unchecked();
  constexpr auto members =
      std::define_static_array(std::meta::members_of(ns_refl, ctx));
  template for (constexpr auto& member : auto(members)) {
    if constexpr (std::meta::has_identifier(member))
      std::cout << std::meta::identifier_of(member) << '\n';
  }
}
