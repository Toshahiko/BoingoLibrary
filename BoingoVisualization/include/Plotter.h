#pragma once

namespace Boingo::Visualization {

struct Range {
  double upper = 0.0 ;
  double lower = 0.0 ;
} ;

class Plotter3D {
public:
  Plotter3D(
      const Range& rangeX,
      const Range& rangeY,
            std::string_view plotType
    ) ;

  ~Plotter3D() ;
  void Execute() const ;

private:
  struct Impl ;
  SMART_PTR_IMPL( Impl )
  Impl_up m_pImpl ;
} ;

}