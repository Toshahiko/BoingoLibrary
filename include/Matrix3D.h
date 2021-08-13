#pragma once
#include <array>
#include "Vector3D.h"

namespace Boingo::Math {

struct Matrix3D {
private:
  std::array<std::array<float, 3>, 3> m_elem ;
public:
  Matrix3D() = default ;

  Matrix3D(
      float n00, float n01, float n02,
      float n10, float n11, float n12,
      float n20, float n21, float n22
    )
  {
    m_elem[0][0] = n00 ;
    m_elem[0][1] = n01 ;
    m_elem[0][2] = n02 ;
    m_elem[1][0] = n10 ;
    m_elem[1][1] = n11 ;
    m_elem[1][2] = n12 ;
    m_elem[2][0] = n20 ;
    m_elem[2][1] = n21 ;
    m_elem[2][2] = n22 ;
  }

  Matrix3D( const Vector3D& a, const Vector3D& b, const Vector3D& c ) {
    m_elem[0][0] = a.m_x ;
    m_elem[0][1] = a.m_y ;
    m_elem[0][2] = a.m_z ;
    m_elem[1][0] = b.m_x ;
    m_elem[1][1] = b.m_y ;
    m_elem[1][2] = b.m_z ;
    m_elem[2][0] = c.m_x ;
    m_elem[2][1] = c.m_y ;
    m_elem[2][2] = c.m_z ;
  }

  const float& operator()( int i, int j ) const {
    return m_elem[i][j] ;
  }

  float& operator()( int i, int j ) {
    return m_elem[i][j] ;
  }

  Vector3D& operator()( int i ) {
    return (*reinterpret_cast<Vector3D*>( m_elem[i].data() ) ) ;
  }

  const Vector3D& operator()( int i ) const {
    return (*reinterpret_cast<const Vector3D*>( m_elem[i].data() ) ) ;
  }
} ;

  Matrix3D operator- ( const Matrix3D& lhs, const Matrix3D& rhs ) {
    return Matrix3D( lhs( 0 ) - rhs( 0 ), lhs( 1 ) - rhs( 1 ), lhs( 2 ) - rhs( 2 ) ) ;
  }

  Matrix3D operator+ ( const Matrix3D& lhs, const Matrix3D& rhs ) {
    return Matrix3D( lhs( 0 ) + rhs( 0 ), lhs( 1 ) + rhs( 1 ), lhs( 2 ) + rhs( 2 ) ) ;
  }


} // namespace Boingo::Math