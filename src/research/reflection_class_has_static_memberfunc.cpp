#include <iostream>
#include <meta>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

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
consteval std::meta::info get_class_by_name() {
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

//**  class_has_static_memberfunc<>
template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_static_memberfunc = []() constexpr -> bool {
  if constexpr (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if constexpr (std::is_same_v<Returntype, unspecified_return_t>)
      return true;
    else if constexpr (sizeof...(Inputtype) != 0) {
      if (std::meta::type_of(member) == ^^Returntype(Inputtype...)) return true;
    } else if (std::meta::return_type_of(member) == ^^Returntype)
      return true;
  }

  return false;
}();

struct X {
  static auto foo(std::string, int) -> std::vector<double>;

  double foos;
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << class_has_static_memberfunc<"X"_ls, "foo"_ls> << std::endl;
  std::cout << class_has_static_memberfunc<"X"_ls, "foo"_ls,
                                           std::vector<double>> << std::endl;
  std::cout
      << class_has_static_memberfunc<"X"_ls, "foo"_ls, std::vector<double>,
                                     std::string, int> << std::endl;

  std::cout << std::endl;

  std::cout
      << class_has_static_memberfunc<"X"_ls, "foo"_ls, double> << std::endl;
  std::cout << class_has_static_memberfunc<"X"_ls, "foo"_ls, const double,
                                           std::string, int> << std::endl;

  std::cout << class_has_static_memberfunc<"XS"_ls, "foo"_ls> << std::endl;

  return 0;
}
