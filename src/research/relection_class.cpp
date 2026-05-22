#include <iostream>
#include <meta>
#include <string_view>

template <std::size_t N>
struct LiteralString {
  consteval LiteralString(const char (&s)[N]) { std::copy(s, s + N, &data[0]); }
  consteval operator std::string_view() const { return {data, data + N - 1}; }

  static constexpr std::size_t size = N;
  char data[N]{};
};

template <LiteralString LS>
constexpr auto operator""_ls() {
  return LS;
}

//** HAS_CLASS

template <LiteralString LS>
concept has_class = []() {
  auto global = ^^::;
  auto unchecked = std::meta::access_context::unchecked();

  auto members =
      std::define_static_array(std::meta::members_of(global, unchecked));

  for (auto mem : members) {
    // First ensure the its a type, otherwise is_class_type throws error.
    if (!std::meta::is_type(mem)) continue;
    if (!std::meta::is_class_type(mem)) continue;

    if ((std::meta::identifier_of(mem) != std::string_view(LS))) continue;

    return true;
  }
  return false;
}();

struct S {
 public:
  int x;
};
struct MyClass;
class MyOtherClass {};
union MyUnion {};

int foo();

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << has_class<"S"_ls> << std::endl;
  std::cout << has_class<"MyClass"_ls> << std::endl;
  std::cout << has_class<"MyOtherClass"_ls> << std::endl;
  std::cout << has_class<"MyUnion"_ls> << std::endl;
  std::cout << has_class<"NonExistent"_ls> << std::endl;
  std::cout << has_class<"foo"_ls> << std::endl;
  std::cout << std::endl;
  return 0;
}