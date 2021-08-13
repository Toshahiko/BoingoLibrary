#include "../doctest/doctest/doctest.h"
#include <include/Matrix3D.h>

TEST_CASE("Matrix3D DefaultConstructor") {
  const auto matrix = Boingo::Math::Matrix3D() ;
  for ( int i = 0 ; i < 3 ; ++i ) {
    for ( int j = 0 ; j < 3 ; ++j ) {
      CHECK( matrix( i, j ) == 0 ) ;
    }
  }
}

TEST_CASE("Matrix3D VectorConstructor") {
  Boingo::Math::Vector3D a = {1, 2, 3} ;
  Boingo::Math::Vector3D b = {4, 5, 6} ;
  Boingo::Math::Vector3D c = {7, 8, 9} ;
  const auto matrix = Boingo::Math::Matrix3D( a, b, c ) ;
  CHECK( matrix( 0 ).m_x == a.m_x ) ;
  CHECK( matrix( 0 ).m_y == a.m_y ) ;
  CHECK( matrix( 0 ).m_z == a.m_z ) ;
  CHECK( matrix( 1 ).m_x == b.m_x ) ;
  CHECK( matrix( 1 ).m_y == b.m_y ) ;
  CHECK( matrix( 1 ).m_z == b.m_z ) ;
  CHECK( matrix( 2 ).m_x == c.m_x ) ;
  CHECK( matrix( 2 ).m_y == c.m_y ) ;
  CHECK( matrix( 2 ).m_z == c.m_z ) ;

}