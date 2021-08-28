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
  , m_plotType(plotType)
  {}
  matplot::vector_2d m_x ;
  matplot::vector_2d m_y ;
  matplot::vector_2d m_z ;
  std::optional<Range> m_rangeX ;
  std::optional<Range> m_rangeY ;
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
{

}

Plotter3D::~Plotter3D() = default ;

void Plotter3D::Execute() const {
  if ( m_pImpl->m_rangeX ) {
    matplot::xlim( { m_pImpl->m_rangeX.value().lower, m_pImpl->m_rangeX.value().upper } );
  }
  if ( m_pImpl->m_rangeY ) {
    matplot::ylim( { m_pImpl->m_rangeY.value().lower, m_pImpl->m_rangeY.value().upper } );
  }

  if ( m_pImpl->m_plotType == "mesh" ) {
    matplot::mesh( m_pImpl->m_x, m_pImpl->m_y, m_pImpl->m_z );
    matplot::show() ;
    std::cout << "ploted" << std::endl ;
    return ;
  }

  std::cout << "Error: plotType " << m_pImpl->m_plotType << " is not founad" << std::endl ;
  return ;
}

}
