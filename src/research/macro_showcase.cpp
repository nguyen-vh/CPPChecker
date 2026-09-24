#include <iostream>

#include "../../include/cxxchecker.hpp"

namespace check_in_here {

struct X {
  double foo();
};
}  // namespace check_in_here

CLASS_HAS_MEMBERFUNC(X, foo)

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << check::class_X_has_memberfunc_foo_v << "\n";

  std::cout << std::endl;
  return 0;
}