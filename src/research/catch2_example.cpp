#define CATCH_CONFIG_MAIN
#include <type_traits>

#include "../../include/catch.hpp"

// class TestClass {
//  public:
//   double getValue() const { return 26; }
// };

TEST_CASE("Check class exists", "[types]") {
  REQUIRE(std::is_class<TestClass>::value);
}

TEST_CASE("Test with class functionality", "[types]") {
  TestClass obj;
  REQUIRE(obj.getValue() == 26);
  REQUIRE(obj.getValue() == static_cast<double>(26));
}
