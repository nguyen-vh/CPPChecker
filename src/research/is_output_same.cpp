#include <algorithm>
#include <concepts>
#include <iostream>
#include <meta>
#include <sstream>
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
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
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

namespace tester {
#include <iostream>
struct foo {
  int foos = 123;
};

auto main(int argv) -> int {
  std::cout << "HELL" << std::endl;
  std::cout << "STATION" << std::endl;
  return 0;
}

}  // namespace tester

template <LiteralString Output>
bool is_output_same() {
  int argc = 0;
  char* argv[] = {nullptr};

  std::ostringstream output_stream;
  std::streambuf* std_buffer = std::cout.rdbuf(output_stream.rdbuf());

  // tester::main(argc, argv);

  // TODO: ADD TEST FOR main(), main(int argc), main(int argc, char** argv)

  std::cout.rdbuf(std_buffer);
  std::string output = output_stream.str();

  std::cout << "Captured output: '" << output << "'" << std::endl;
  std::string_view expected = Output;
  std::cout << "Expected output: '" << expected << "'" << std::endl;

  if (!output.empty() && output.ends_with('\n')) {
    output.pop_back();
  }

  return expected == output;
}

double foo;

auto main(int argc /*, char* argv[]*/) -> int {
  std::cout << has_free_variable<"foos"_ls> << std::endl;
  std::cout << has_free_variable<"foo"_ls> << std::endl;
  std::cout << has_free_variable<"foo"_ls, double> << std::endl;
  std::cout << has_free_variable<"foo"_ls, int> << std::endl;

  std::cout << "_____" << std::endl;
  std::cout << is_output_same<"HELL\nSTATION"_ls> << std::endl;
  return 0;
}
