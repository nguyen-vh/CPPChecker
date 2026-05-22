// Source - https://stackoverflow.com/q/79913644
// Posted by Oersted, modified by 康桓瑋
// Retrieved 2026-04-30, License - CC BY-SA 4.0

#include <iostream>
#include <meta>
#include <string>
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

template <typename T, LiteralString LS, typename out, typename... in>
concept has_member_function_named = []() {
  auto members =
      std::meta::members_of(^^T, std::meta::access_context::current());

  for (auto mem : members) {
    if (!std::meta::is_function(mem)) continue;
    // Need to check has_identifier, otherwise I've got issues with
    // constructors
    if (std::meta::has_identifier(mem) &&
        (std::meta::identifier_of(mem) != std::string_view(LS)))
      continue;
    if (std::meta::has_identifier(mem)) {
      if (std::meta::type_of(mem) == ^^out(in...)) return true;
    }
  }
  return false;
}();

struct X {
  int foo(int, std::string);
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << has_member_function_named<X, "foo"_ls, int, int,
                                         std::string> << std::endl;
  return 0;
}
