#pragma once
#include <cmath>

namespace Boingo::Math {

struct Vector3D {
  float m_x, m_y, m_z ;
  Vector3D() = default ;
  Vector3D( float x, float y, float z ) : m_x(x), m_y(y), m_z(z) {

  }

  const float& operator[]( int i ) const {
    return ( (&m_x)[i] ) ;
  }

  float& operator[]( int i ) {
    return ( (&m_x)[i] ) ;
  }

  Vector3D& operator *=( float s ) {
    m_x *= s ;
    m_y *= s ;
    m_z *= s ;
    return ( *this ) ;
  }

  Vector3D& operator /=( float s ) {
    const auto d = 1.0F/s ;
    m_x *= d ;
    m_y *= d ;
    m_z *= d ;
    return ( *this ) ;
  }

  Vector3D& operator +=( Vector3D& v ) {
    m_x += v.m_x ;
    m_y += v.m_y ;
    m_z += v.m_z ;
    return ( *this ) ;
  }

  Vector3D& operator -=( Vector3D& v ) {
    m_x -= v.m_x ;
    m_y -= v.m_y ;
    m_z -= v.m_z ;
    return ( *this ) ;
  }
} ;

inline Vector3D operator *( const Vector3D& v, const float s ) {
  return Vector3D( v.m_x*s, v.m_y*s, v.m_z*s ) ;
}

inline Vector3D operator *( const float s, const Vector3D& v ) {
  return v*s ;
}

inline Vector3D operator /( const Vector3D& v, const float s ) {
  const auto d = 1.0F/s ;
  return Vector3D( v.m_x*d, v.m_y*d, v.m_z*d ) ;
}

inline Vector3D operator -( const Vector3D& v ) {
  return Vector3D( -v.m_x, -v.m_y, -v.m_z ) ;
}

inline float Magnitude( const Vector3D& v ) {
  return std::sqrt( v.m_x*v.m_x + v.m_y*v.m_y + v.m_z*v.m_z ) ;
}

inline Vector3D Normalize( const Vector3D& v ) {
  return v/Magnitude( v ) ;
}

inline Vector3D operator +( const Vector3D& lhs, const Vector3D& rhs ) {
  return Vector3D( lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z ) ;
}

inline Vector3D operator -( const Vector3D& lhs, const Vector3D& rhs ) {
  return Vector3D( lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z ) ;
}

} // namespace Boingo::Math