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

template <LiteralString Name>
consteval auto get_class_by_name() -> std::meta::info {
  auto global = ^^::;
  auto members =
      std::meta::members_of(global, std::meta::access_context::unchecked());

  for (auto mem : members) {
    if (!std::meta::is_type(mem)) continue;
    if (!std::meta::is_class_type(mem)) continue;
    if (std::meta::identifier_of(mem) == std::string_view{Name}) return mem;
  }
  return {};
}

template <LiteralString T>
concept has_class = (get_class_by_name<T>() != std::meta::info{});

struct unspecified_return_t {};

//** CLASS_HAS_MEMBERVAR

template <LiteralString T, LiteralString LS,
          typename TYPE = unspecified_return_t>
concept class_has_membervar = []() {
  if (!has_class<T>) return false;

  auto members = std::meta::members_of(get_class_by_name<T>(),
                                       std::meta::access_context::current());

  for (const auto& mem : members) {
    if (!std::meta::is_nonstatic_data_member(mem)) continue;

    if (std::meta::has_identifier(mem) &&
        std::meta::identifier_of(mem) != std::string_view(LS))
      continue;

    if (std::meta::has_identifier(mem)) {
      if constexpr (std::is_same_v<TYPE, unspecified_return_t>) {
        return true;
      } else if (std::meta::type_of(mem) == ^^TYPE) {
        return true;
      }
    }
  }
  return false;
}();

struct X {
  int foo(long long int, std::string_view);
  int foos(double, std::string);

  static fooo(int);

  double fooos;
};

struct XY {};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << class_has_membervar<"X"_ls, "fooos"_ls, double> << std::endl;
  std::cout << class_has_membervar<"XS"_ls, "fooos"_ls, double> << std::endl;
  std::cout << class_has_membervar<"X"_ls, "fooos"_ls> << std::endl;
  std::cout << class_has_membervar<"X"_ls, "fooo"_ls, double> << std::endl;
  return 0;
}