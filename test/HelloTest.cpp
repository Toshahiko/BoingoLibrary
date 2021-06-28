// #define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest/doctest/doctest.h"

#include <src/HelloFunc.h>

TEST_CASE("Hello") {

  REQUIRE(Boingo::HelloFunc() == "Hello!");
}
