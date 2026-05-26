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

template <LiteralString Memberfunc, typename Returntype = unspecified_return_t,
          typename... Inputtype>
concept has_free_static_function = []() {
  std::string_view full_name{Memberfunc};
  auto scope = ^^::;

  while (!full_name.empty()) {
    auto pos = full_name.find("::");
    bool b_last_pos = (pos == std::string_view::npos);
    std::string_view part_of_name =
        b_last_pos ? full_name : full_name.substr(0, pos);

    if (part_of_name.empty()) break;

    bool b_found = false;

    auto members =
        std::meta::members_of(scope, std::meta::access_context::unchecked());

    for (const auto& member : members) {
      if (std::meta::has_identifier(member) &&
          (std::meta::identifier_of(member) == part_of_name)) {
        if (b_last_pos) {
          if (!std::meta::has_internal_linkage(member)) continue;
          if (!std::meta::is_function(member)) continue;

          if constexpr (std::is_same_v<Returntype, unspecified_return_t>) {
            return true;
          } else if constexpr (sizeof...(Inputtype) != 0) {
            if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
              return true;
          } else if (std::meta::return_type_of(std::meta::type_of(member)) ==
                     ^^Returntype) {
            return true;
          }
        }

        if (std::meta::is_namespace(member)) {
          scope = member;
          b_found = true;

          break;
        }

        return false;
      }
    }

    if (!b_found) return false;

    full_name.remove_prefix(b_last_pos ? full_name.size() : pos + 2);
  }

  return false;
}();

namespace test {

static float goo();

namespace tester {

static int joo();
}
}  // namespace test

static double foo(int);

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << has_free_static_function<"foo"_ls> << std::endl;
  std::cout << has_free_static_function<"foo"_ls, double> << std::endl;
  std::cout << has_free_static_function<"foo"_ls, double, int> << std::endl;

  std::cout << std::endl;

  std::cout << has_free_static_function<"foos"_ls> << std::endl;
  std::cout << has_free_static_function<"foo"_ls, int> << std::endl;

  std::cout << std::endl;

  std::cout << has_free_static_function<"test::goo"_ls, float> << std::endl;
  std::cout
      << has_free_static_function<"test::goo"_ls, int_fast16_t> << std::endl;

  std::cout << std::endl;

  std::cout
      << has_free_static_function<"test::tester::joo"_ls, int> << std::endl;
  std::cout
      << has_free_static_function<"test::tester::joo"_ls, float> << std::endl;

  std::cout << std::endl;
  return 0;
}
