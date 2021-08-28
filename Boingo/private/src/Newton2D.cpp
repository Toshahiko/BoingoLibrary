#include <Boingo/include/Newton2D.h>

namespace Boingo {

Newton2D::Newton2D(
    const Function2D& diverge_x,
    const Function2D& diverge_y,
    const Point2D& initial_value
  )
  : m_diverge_x( diverge_x )
  , m_diverge_y( diverge_y )
  , m_initial_value( initial_value )
  {}

  std::pair<matplot::vector_1d, matplot::vector_1d>
  Newton2D::Execute() {
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
      tmp_xy.first = tmp_xy.first - diverge_x ;
      tmp_xy.second = tmp_xy.second - diverge_y ;

      x_plot.push_back( tmp_xy.first ) ;
      y_plot.push_back( tmp_xy.second ) ;

      ++count ;
      std::cout << "count: " << count << " " ;
      std::cout << tmp_xy.first << " " << tmp_xy.second << std::endl ;
    }

    return std::make_pair( x_plot, y_plot ) ;
  }

}