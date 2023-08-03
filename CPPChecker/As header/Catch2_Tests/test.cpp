#define CATCH_CONFIG_MAIN 
#include <catch2/catch.hpp> 

// test
int add(int a, int b) {
    return a + b;
}

TEST_CASE("Addition Test") {
    REQUIRE(add(2, 3) == 5);
    REQUIRE(add(-2, 5) == 3);
    REQUIRE(add(0, 0) == 0);
}
