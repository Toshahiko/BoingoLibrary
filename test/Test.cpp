#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest/doctest/doctest.h"

#include <tuple>

namespace web {
namespace http {
enum class status_codes {
  OK,
  NG,
} ;
}

namespace json {
  auto value( auto hello ) { return hello; }
} // namespace json

}

class responder{
public:
auto prepare_response( auto name ) {
  return std::make_pair( web::http::status_codes::OK, web::json::value("Hello, Bob!") ) ;
}

} ;

TEST_CASE("Basic responses") {
  auto name = "Bob";
  auto code_and_string = responder{}.prepare_response(name);
  REQUIRE(code_and_string.first == web::http::status_codes::OK);
  REQUIRE(code_and_string.second == web::json::value("Hello, Bob!"));
}
