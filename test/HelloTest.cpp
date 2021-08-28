// #define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest/doctest/doctest.h"

#include <BoingoApi/include/HelloFunc.h>

TEST_CASE("Hello") {

  REQUIRE(Boingo::HelloFunc() == "Hello!");
}
