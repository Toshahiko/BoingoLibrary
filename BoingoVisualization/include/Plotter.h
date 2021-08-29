#pragma once

namespace Boingo::Visualization {

struct Range {
  double upper = 0.0 ;
  double lower = 0.0 ;
} ;

class Plotter3D {
public:
  Plotter3D(
      std::vector<std::vector<double>>&& x,
      std::vector<std::vector<double>>&& y,
      std::vector<std::vector<double>>&& z,
      std::string_view plotType
    ) ;

  ~Plotter3D() ;
  void Execute() const ;
  void SetRangeX( const Range& rangeX ) ;
  void SetRangeY( const Range& rangeY ) ;
  void SetRangeZ( const Range& rangeZ ) ;

private:
  bool HasRangeX() const ;
  bool HasRangeY() const ;
  bool HasRangeZ() const ;
  Range RangeX() const ;
  Range RangeY() const ;
  Range RangeZ() const ;
  void Initialize() const ;
  void Plot() const ;

private:
  struct Impl ;
  SMART_PTR_IMPL( Impl )
  Impl_up m_pImpl ;
} ;

}