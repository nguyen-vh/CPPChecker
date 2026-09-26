// Source - https://stackoverflow.com/a/79939812
// Posted by Artyer, modified by community. See post 'Timeline' for change
// history Retrieved 2026-06-20, License - CC BY-SA 4.0

#include <iostream>
#include <meta>

int flow;
int glow();

int main() {
  constexpr auto members = std::define_static_array(
      std::meta::members_of(^^::, std::meta::access_context::unchecked()));

  template for (constexpr auto& member : auto(members)) {
    if constexpr (std::meta::has_identifier(member))
      std::cout << std::meta::identifier_of(member) << '\n';
  }
}
