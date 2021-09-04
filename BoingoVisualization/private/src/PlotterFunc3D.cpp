#include <include/pch.h>
#include "BoingoVisualization/include/PlotterFunc3D.h"
#include <matplot/matplot.h>

namespace Boingo::Visualization {

struct PlotterFunc3D::Impl {
  Impl(
      const std::function<double( double, double )>& func,
      std::string_view plotType
    ) : m_funcx( func ), m_plotType( plotType )
  {
  }

  Impl(
      const std::function<double( double, double )>& funcx,
      const std::function<double( double, double )>& funcy,
      const std::function<double( double, double )>& funcz,
      std::string_view plotType
    ) : m_funcx( funcx ), m_funcy( funcy ), m_funcz( funcz ), m_plotType( plotType )
  {
  }

  std::function<double( double, double )> m_funcx ;
  std::optional<std::function<double( double, double )>> m_funcy ;
  std::optional<std::function<double( double, double )>> m_funcz ;
  std::optional<Range> m_rangeX ;
  std::optional<Range> m_rangeY ;
  std::optional<Range> m_rangeZ ;
  std::string_view m_plotType ;
} ;

PlotterFunc3D::PlotterFunc3D(
    const std::function<double( double, double )>& funcx,
    const std::function<double( double, double )>& funcy,
    const std::function<double( double, double )>& funcz,
    std::string_view plotType
  ) : m_pImpl( std::make_unique<Impl>( funcx, funcy, funcz, plotType ) )
{
}

PlotterFunc3D::PlotterFunc3D(
    const std::function<double( double, double )>& func,
    std::string_view plotType
  ) : m_pImpl( std::make_unique<Impl>( func, plotType ) )
{
}

PlotterFunc3D::~PlotterFunc3D() = default ;

void PlotterFunc3D::Execute() const
{
  Initialize() ;
  Plot() ;
}

void PlotterFunc3D::SetRangeX( const Range& rangeX ) {
  m_pImpl->m_rangeX = rangeX ;
}

void PlotterFunc3D::SetRangeY( const Range& rangeY ) {
  m_pImpl->m_rangeY = rangeY ;
}

void PlotterFunc3D::SetRangeZ( const Range& rangeZ ) {
  m_pImpl->m_rangeZ = rangeZ ;
}

bool PlotterFunc3D::HasRangeX() const {
  return m_pImpl->m_rangeX.has_value() ;
}

bool PlotterFunc3D::HasRangeY() const {
  return m_pImpl->m_rangeY.has_value() ;
}

bool PlotterFunc3D::HasRangeZ() const {
  return m_pImpl->m_rangeZ.has_value() ;
}

Range PlotterFunc3D::RangeX() const {
  assert( HasRangeX() );
  return m_pImpl->m_rangeX.value() ;
}

Range PlotterFunc3D::RangeY() const {
  assert( HasRangeY() );
  return m_pImpl->m_rangeY.value() ;
}

Range PlotterFunc3D::RangeZ() const {
  assert( HasRangeZ() );
  return m_pImpl->m_rangeZ.value() ;
}

void PlotterFunc3D::Initialize() const {
  if ( HasRangeX() ) {
    matplot::xlim( { RangeX().lower, RangeX().upper } );
  }
  if ( HasRangeY() ) {
    matplot::ylim( { RangeY().lower, RangeY().upper } );
  }
  if ( HasRangeZ() ) {
    matplot::ylim( { RangeZ().lower, RangeZ().upper } );
  }
}

void PlotterFunc3D::Plot() const {
  if ( m_pImpl->m_plotType == "surf" ) {
    matplot::fsurf( m_pImpl->m_funcx,
                    m_pImpl->m_funcy.value(),
                    m_pImpl->m_funcz.value(),
                    { 0, 2 * matplot::pi, 0, matplot::pi }
                  ) ;
  } else if ( m_pImpl->m_plotType == "mesh" ) {
    matplot::fmesh( m_pImpl->m_funcx,
                    m_pImpl->m_funcy.value(),
                    m_pImpl->m_funcz.value(),
                    std::array<double, 4>{ 0, 2 * matplot::pi, 0, matplot::pi }
                  ) ;
  }
}

}