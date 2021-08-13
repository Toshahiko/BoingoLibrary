#include "../doctest/doctest/doctest.h"
#include <include/Vector3D.h>

TEST_CASE("DefaultConstructor") {
  auto vec = Boingo::Math::Vector3D() ;
  CHECK( vec.m_x == 0.0 );
  CHECK( vec.m_y == 0.0 );
  CHECK( vec.m_z == 0.0 );
}

TEST_CASE("Vector3D") {
  auto vec = Boingo::Math::Vector3D( 1.0, 2.0, 3.0 ) ;
  SUBCASE("Constructor") {
    CHECK( vec.m_x == 1.0 );
    CHECK( vec.m_y == 2.0 );
    CHECK( vec.m_z == 3.0 );
  }

  SUBCASE("Access") {
    CHECK( vec[0] == 1.0 );
    CHECK( vec[1] == 2.0 );
    CHECK( vec[2] == 3.0 );
  }

  SUBCASE("Multiple") {
    vec *= 2 ;
    CHECK( vec[0] == 2.0 );
    CHECK( vec[1] == 4.0 );
    CHECK( vec[2] == 6.0 );
  }

  SUBCASE("Divide") {
    vec /= 2 ;
    CHECK( vec[0] == 0.5 );
    CHECK( vec[1] == 1.0 );
    CHECK( vec[2] == 1.5 );
  }

  SUBCASE("Magnitude") {
    CHECK( Boingo::Math::Magnitude( vec ) == std::sqrt( 14.0f ) ) ;
  }

  SUBCASE("Normalize") {
    CHECK( Boingo::Math::Magnitude( Boingo::Math::Normalize( vec ) ) <= 1.0f ) ;
  }
}