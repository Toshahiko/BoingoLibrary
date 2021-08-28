#include <BoingoNumerical/include/GradientDescent.h>
#include <matplot/matplot.h>

namespace Boingo::Numerical {

namespace {
}

GradientDescent::GradientDescent(
    const Function2D& func,
    const Function2D& diverge_x,
    const Function2D& diverge_y,
    const Point2D& initial_value,
    const double step_width
  )
  : m_func( func )
  , m_diverge_x( diverge_x )
  , m_diverge_y( diverge_y )
  , m_initial_value( initial_value )
  , m_step_width( step_width )
{}

std::pair<matplot::vector_1d, matplot::vector_1d>
GradientDescent::Execute() {
  auto tmp_xy = m_initial_value ;
  matplot::vector_1d x_plot, y_plot ;
  x_plot.push_back( tmp_xy.first ) ;
  y_plot.push_back( tmp_xy.second ) ;
  constexpr double tolerance = 1.0e-5 ;
  const auto norm = []( const auto diverge_x, const auto diverge_y ) {
    return diverge_x*diverge_x + diverge_y*diverge_y ;
  } ;
  int count = 0 ;
  for ( int i = 0 ; i < 100 ; ++i ) {
    const auto diverge_x = m_diverge_x( tmp_xy.first, tmp_xy.second ) ;
    const auto diverge_y = m_diverge_y( tmp_xy.first, tmp_xy.second ) ;
    if ( norm( diverge_x, diverge_y ) < tolerance ) break ;
    const auto step_width = StepWidth( tmp_xy.first, tmp_xy.second, diverge_x, diverge_y ) ;
    tmp_xy.first = tmp_xy.first - step_width*diverge_x ;
    tmp_xy.second = tmp_xy.second - step_width*diverge_y ;
    x_plot.push_back( tmp_xy.first ) ;
    y_plot.push_back( tmp_xy.second ) ;
    ++count ;
    std::cout << "count: " << count << " " ;
    std::cout << tmp_xy.first << " " << tmp_xy.second << std::endl ;
  }
  return std::make_pair( x_plot, y_plot ) ;
}
double GradientDescent::StepWidth( const double x, const double y, const double d_x, const double d_y ) {
  constexpr double rho = 0.8, c1 = 0.8 ;
  for ( int i = 0 ; i < 100 ; ++i ) {
    const auto lhs = m_func( x - m_step_width*d_x, y - m_step_width*d_y ) ;
    const auto rhs = m_func( x, y ) - c1*m_step_width*( d_x*d_x + d_y*d_y ) ;
    if ( lhs < rhs ) break ;
    m_step_width *= rho ;
  }
  return m_step_width ;
}

}