#include <iostream>
#include <meta>
#include <string_view>
#include <type_traits>

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

struct unspecified_return_t {};

template <LiteralString Membervar, typename Type = unspecified_return_t>
concept has_free_variable = []() {
  auto global_namespace = ^^::;
  auto members = std::meta::members_of(global_namespace,
                                       std::meta::access_context::current());

  for (const auto& member : members) {
    if (!std::meta::has_internal_linkage(member)) continue;
    if (!std::meta::is_variable(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>) {
        return true;
      } else if (std::meta::type_of(member) == ^^Type) {
        return true;
      }
    }
  }
  return false;
}();

static double foo;

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << has_free_variable<"foos"_ls> << std::endl;
  std::cout << has_free_variable<"foo"_ls> << std::endl;
  std::cout << has_free_variable<"foo"_ls, double> << std::endl;
  std::cout << has_free_variable<"foo"_ls, int> << std::endl;

  return 0;
}
