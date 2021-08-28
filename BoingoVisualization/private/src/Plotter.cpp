#include <include/pch.h>
#include <BoingoVisualization/include/Plotter.h>

namespace Boingo::Visualization {

struct Plotter3D::Impl {
  Impl( const Range& rangeX, const Range& rangeY, std::string_view plotType )
  : m_rangeX(rangeX), m_rangeY(rangeY), m_plotType(plotType)
  {}
  Range m_rangeX ;
  Range m_rangeY ;
  std::string_view m_plotType ;
} ;

Plotter3D::Plotter3D(
    const Range& rangeX,
    const Range& rangeY,
          std::string_view plotType
  ) : m_pImpl( std::make_unique<Impl>( rangeX, rangeY, plotType ) )
{

}

Plotter3D::~Plotter3D() = default ;

void Plotter3D::Execute() const {

}

}
