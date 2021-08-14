#include <include/pch.h>
#include "src/HelloFunc.h"
#include <src/SettingManager.h>
#include <include/Debugger.h>
#include <include/Vector3D.h>
#include <matplot/matplot.h>

namespace {
void FourierTransform() {
}

double func( double x, double y ) {
  return x*x*x + -2*x*x + x*x*y + 2*y*y ;
}

const auto DivergeFuncX( double x, double y ) {
  return 3*x*x - 4*x + 2*x*y ;
}

const auto DivergeFuncY( double x, double y ) {
  return x*x + 4*y ;
}

class Newton2D {
  public:
  Newton2D( const auto& diverge_x, const auto& diverge_y, const auto& initial_value, const double delta )
  : m_diverge_x( diverge_x ), m_diverge_y( diverge_y ), m_initial_value( initial_value ), m_delta( delta )
  {}

  std::pair<matplot::vector_1d, matplot::vector_1d>
  Execute() const {
    auto tmp_xy = m_initial_value ;

    matplot::vector_1d x_plot ;
    matplot::vector_1d y_plot ;
    x_plot.push_back( tmp_xy.first ) ;
    y_plot.push_back( tmp_xy.second ) ;
    for ( int i = 0 ; i < 100 ; ++i ) {
      tmp_xy.first = tmp_xy.first - m_delta*m_diverge_x( tmp_xy.first, tmp_xy.second ) ;
      tmp_xy.second = tmp_xy.second - m_delta*m_diverge_y( tmp_xy.first, tmp_xy.second ) ;

      x_plot.push_back( tmp_xy.first ) ;
      y_plot.push_back( tmp_xy.second ) ;

      std::cout << tmp_xy.first << " " << tmp_xy.second << std::endl ;
    }

    return std::make_pair( x_plot, y_plot ) ;
  }

  private:
    const std::function<double(double,double)> m_diverge_x ;
    const std::function<double(double,double)> m_diverge_y ;
    const std::pair<double, double>            m_initial_value ;
    const double                               m_delta ;
} ;

}

int main() {
  Boingo::HelloFunc() ;

  Boingo::App::SettingManager::Instance().SetBGColor( 0, 255, 255 ) ;

  const auto anony = Boingo::Debug::decorate_debug( [](){ return 0 ;}, "anonymous" ) ;

  const auto [x, y] = matplot::meshgrid( matplot::linspace( -5.0, 5.0 ), matplot::linspace( -5.0, 5.0 ) ) ;

  const auto z = matplot::transform( x, y, func ) ;
  matplot::mesh( x, y, z ) ;
  matplot::hold( matplot::on ) ;

  const matplot::vector_1d least_x = {2, 4, 0} ;
  const matplot::vector_1d least_y = {-1, -4, 0} ;
  const auto least_z = matplot::transform( least_x, least_y, func ) ;
  matplot::scatter3( least_x, least_y, least_z ) ;

  Newton2D newton2d( DivergeFuncX, DivergeFuncY, std::make_pair( 0.2, 0.2 ), 0.01 ) ;
  const auto [solution_x, solution_y] = newton2d.Execute() ;
  const auto solution_z = matplot::transform( solution_x, solution_y, func ) ;
  matplot::scatter3( solution_x, solution_y, solution_z ) ;

  matplot::show() ;
  return 0 ;
}