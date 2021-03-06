#pragma once
#include "BoingoVisualization.h"
#include "IRangePlot.h"

namespace Boingo::Visualization {

class Plotter3D final : public IRangePlot {
public:
  Plotter3D(
      std::vector<std::vector<double>>&& x,
      std::vector<std::vector<double>>&& y,
      std::vector<std::vector<double>>&& z,
      std::string_view plotType
    ) ;

  ~Plotter3D() ;
  void Execute() const ;
  void SetRangeX( const Range& rangeX ) final ;
  void SetRangeY( const Range& rangeY ) final ;
  void SetRangeZ( const Range& rangeZ ) final ;

private:
  bool HasRangeX() const final ;
  bool HasRangeY() const final ;
  bool HasRangeZ() const final ;
  Range RangeX() const final ;
  Range RangeY() const final ;
  Range RangeZ() const final ;
  void Initialize() const ;
  void Plot() const ;

private:
  struct Impl ;
  SMART_PTR_IMPL( Impl )
  Impl_up m_pImpl ;
} ;

}