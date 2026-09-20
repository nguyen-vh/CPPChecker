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

template <LiteralString ClassName>
concept has_class = (get_class_by_name<ClassName>() != std::meta::info{});

template <LiteralString Class>
concept class_has_move_assignment_operator = []() constexpr -> bool {
  if constexpr (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (auto member : members) {
    if (std::meta::is_move_assignment(member) &&
        std::meta::is_user_declared(member))
      return true;
  }
  return false;
}();

class X {
 private:
  int x;
  double y;
  int z;

 public:
  // X() {}
  // X(int x, double y, int z) { std::cout << "Hello World!"; }
  // X(X& other) : x(other.x), y(other.y), z(other.z) {}
  // X(X&& other) noexcept : x(other.x), y(other.y), z(other.z) {other.x =
  // 0;other.y = 0.0;other.z = 0;}
  X& operator=(const X& other) {
    if (this != &other) {
      x = other.x;
      y = other.y;
      z = other.z;
    }
    return *this;
  }
  X& operator=(X&& other) noexcept {
    if (this != &other) {
      x = other.x;
      y = other.y;
      z = other.z;
      other.x = 0;
      other.y = 0.0;
      other.z = 0;
    }
    return *this;
  }

  ~X() = default;

  double foo();
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << class_has_move_assignment_operator<"X"_ls> << "\n";

  std::cout << std::endl;
  return 0;
}