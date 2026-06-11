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

template <LiteralString Class>
consteval auto get_class_by_name() -> std::meta::info {
  std::string_view full_name{Class};
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
      if (!std::meta::has_identifier(member) ||
          std::meta::identifier_of(member) != part_of_name)
        continue;

      if (b_last_pos) {
        if (!std::meta::is_type(member)) continue;
        if (!std::meta::is_class_type(member)) continue;

        return member;
      }

      if (std::meta::is_namespace(member)) {
        scope = member;
        b_found = true;

        break;
      }

      return {};
    }

    if (!b_found) return {};

    full_name.remove_prefix(b_last_pos ? full_name.size() : pos + 2);
  }

  return {};
}

struct unspecified_return_t {};

template <LiteralString ClassName>
concept has_class = (get_class_by_name<ClassName>() != std::meta::info{});

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t>
concept class_has_member_template = []() constexpr -> bool {
  if constexpr (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_template(member)) continue;

    if (!std::meta::has_identifier(member) ||
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if constexpr (std::is_same_v<Returntype, unspecified_return_t>) return true;
    // if (std::meta::template_return_type_of(member) == ^^Returntype) return
    // true;
  }

  return false;
}();

namespace test {
class X {
 public:
  template <typename T>
  void log(const T& value) {
    std::cout << "Logging: " << value << std::endl;
  }

  void foo();
};

}  // namespace test

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << class_has_member_template<"test::X"_ls, "log"_ls> << std::endl;
  std::cout
      << class_has_member_template<"test::X"_ls, "log"_ls, void> << std::endl;

  std::cout << std::endl;

  std::cout << class_has_member_template<"test::X"_ls, "goo"_ls> << std::endl;
  std::cout << class_has_member_template<"test::X"_ls, "foo"_ls> << std::endl;
  std::cout
      << class_has_member_template<"test::X"_ls, "log"_ls, int> << std::endl;
  return 0;
}