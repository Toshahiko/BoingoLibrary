#pragma once
#include "BoingoVisualization.h"
#include "IRangePlot.h"

namespace Boingo::Visualization {

class PlotterFunc3D final : public IRangePlot {
public:
  PlotterFunc3D(
      const std::function<double( double, double )>& funcx,
      const std::function<double( double, double )>& funcy,
      const std::function<double( double, double )>& funcz,
      std::string_view plotType
    ) ;

  PlotterFunc3D(
      const std::function<double( double, double )>& func,
      std::string_view plotType
    ) ;

  ~PlotterFunc3D() ;
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
  SMART_PTR_IMPL( Impl ) ;
  Impl_up m_pImpl ;
} ;
}