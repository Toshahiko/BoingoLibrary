#include <include/pch.h>
#include <BoingoVisualization/include/Plotter.h>
#include <matplot/matplot.h>

namespace Boingo::Visualization {

struct Plotter3D::Impl {
  Impl(
      matplot::vector_2d&& x,
      matplot::vector_2d&& y,
      matplot::vector_2d&& z,
      std::string_view     plotType
    )
  : m_x( std::move( x ) )
  , m_y( std::move( y ) )
  , m_z( std::move( z ) )
  , m_plotType( plotType )
  {}
  matplot::vector_2d m_x ;
  matplot::vector_2d m_y ;
  matplot::vector_2d m_z ;
  std::optional<Range> m_rangeX ;
  std::optional<Range> m_rangeY ;
  std::optional<Range> m_rangeZ ;
  std::string_view m_plotType ;
} ;

Plotter3D::Plotter3D(
    std::vector<std::vector<double>>&& x,
    std::vector<std::vector<double>>&& y,
    std::vector<std::vector<double>>&& z,
    std::string_view                   plotType
  ) : m_pImpl( std::make_unique<Impl>(
      std::move( x )
    , std::move( y )
    , std::move( z )
    , plotType ) )
{}

Plotter3D::~Plotter3D() = default ;

void Plotter3D::Execute() const {
  Initialize() ;
  Plot() ;
}

bool Plotter3D::HasRangeX() const {
  return m_pImpl->m_rangeX.has_value() ;
}

bool Plotter3D::HasRangeY() const {
  return m_pImpl->m_rangeY.has_value() ;
}

bool Plotter3D::HasRangeZ() const {
  return m_pImpl->m_rangeZ.has_value() ;
}

Range Plotter3D::RangeX() const {
  assert( HasRangeX() );
  return m_pImpl->m_rangeX.value() ;
}

Range Plotter3D::RangeY() const {
  assert( HasRangeY() );
  return m_pImpl->m_rangeY.value() ;
}

Range Plotter3D::RangeZ() const {
  assert( HasRangeZ() );
  return m_pImpl->m_rangeZ.value() ;
}

void Plotter3D::SetRangeX( const Range& rangeX ) {
  m_pImpl->m_rangeX = rangeX ;
}

void Plotter3D::SetRangeY( const Range& rangeY ) {
  m_pImpl->m_rangeY = rangeY ;
}

void Plotter3D::SetRangeZ( const Range& rangeZ ) {
  m_pImpl->m_rangeZ = rangeZ ;
}

void Plotter3D::Initialize() const {
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

void Plotter3D::Plot() const {
  if ( m_pImpl->m_plotType == "mesh" ) {
    matplot::mesh( m_pImpl->m_x, m_pImpl->m_y, m_pImpl->m_z );
    matplot::show() ;
    return ;
  }

  if ( m_pImpl->m_plotType == "surf" ) {
    matplot::surf( m_pImpl->m_x, m_pImpl->m_y, m_pImpl->m_z );
    matplot::show() ;
    return ;
  }

  std::cout << "Error: plotType " << m_pImpl->m_plotType << " is not founad" << std::endl ;
  return ;
}

}
