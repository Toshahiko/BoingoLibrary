#include <include/pch.h>
#include <include/Debugger.h>
#include <include/Vector3D.h>
#include <Boingo/include/GradientDescent.h>
#include <Boingo/include/Newton2D.h>

namespace {

double func( double x, double y ) {
  return x*x*x + -2*x*x + x*x*y + 2*y*y ;
}

const auto DivergeFuncX( double x, double y ) {
  return 3*x*x - 4*x + 2*x*y ;
}

const auto DivergeFuncY( double x, double y ) {
  return x*x + 4*y ;
}

}

int main() {

  const auto anony = Boingo::Debug::decorate_debug( [](){ return 0 ;}, "anonymous" ) ;

  const auto [x, y] = matplot::meshgrid( matplot::linspace( -5.0, 5.0 ), matplot::linspace( -5.0, 5.0 ) ) ;

  const auto z = matplot::transform( x, y, func ) ;
  matplot::mesh( x, y, z ) ;
  matplot::hold( matplot::on ) ;

  const matplot::vector_1d least_x = {2, 4, 0} ;
  const matplot::vector_1d least_y = {-1, -4, 0} ;
  const auto least_z = matplot::transform( least_x, least_y, func ) ;
  matplot::scatter3( least_x, least_y, least_z ) ;

  // Boingo::Newton2D newton( DivergeFuncX, DivergeFuncY, std::make_pair( 0.2, 0.2 ) ) ;

  Boingo::GradientDescent gradientDescent( func, DivergeFuncX, DivergeFuncY, std::make_pair( 0.2, 0.2 ), 0.1 ) ;
  // const auto [solution_x, solution_y] = gradientDescent.Execute() ;
  // const auto solution_z = matplot::transform( solution_x, solution_y, func ) ;
  // matplot::scatter3( solution_x, solution_y, solution_z ) ;

  matplot::show() ;
  return 0 ;
}