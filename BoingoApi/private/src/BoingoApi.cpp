#include <include/pch.h>
#include <BoingoApi/include/BoingoApi.h>
#include <BoingoNumerical/include/GradientDescent.h>
#include <BoingoNumerical/include/Newton2D.h>
#include <BoingoVisualization/include/Plotter.h>
#include <BoingoVisualization/include/PlotterFunc3D.h>

namespace Boingo::Api {

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

void StartApi() {
  // auto [x, y] = matplot::meshgrid( matplot::linspace( -5.0, 5.0 ), matplot::linspace( -5.0, 5.0 ) ) ;
  // auto z = matplot::transform( x, y, func ) ;

  // Visualization::Plotter3D plotter3D( std::move( x ), std::move( y ), std::move( z ), "surf" ) ;

  // plotter3D.SetRangeX( { 0.0, 1.0 } ) ;
  // plotter3D.Execute() ;
  // matplot::hold( matplot::on ) ;

  // matplot::fmesh( []( double x, double y ) { return x*y ; } ) ;

  auto r = [](double u, double v) { return 2 + sin(7 * u + 5 * v); };
  auto funx = [r](double u, double v) { return r(u, v) * cos(u) * sin(v); };
  auto funy = [r](double u, double v) { return r(u, v) * sin(u) * sin(v); };
  auto funz = [r](double u, double v) { return r(u, v) * cos(v); };
  Visualization::PlotterFunc3D plotterFunc3D( funx, funy, funz, "mesh" ) ;
  plotterFunc3D.Execute() ;

  // const matplot::vector_1d least_x = {2, 4, 0} ;
  // const matplot::vector_1d least_y = {-1, -4, 0} ;
  // const auto least_z = matplot::transform( least_x, least_y, func ) ;
  // matplot::scatter3( least_x, least_y, least_z ) ;

  // Boingo::Numerical::Newton2D newton( DivergeFuncX, DivergeFuncY, std::make_pair( 0.2, 0.2 ) ) ;
  // Boingo::Numerical::GradientDescent gradientDescent( func, DivergeFuncX, DivergeFuncY, std::make_pair( 0.2, 0.2 ), 0.1 ) ;
  // const auto [solution_x, solution_y] = gradientDescent.Execute() ;
  // const auto solution_z = matplot::transform( solution_x, solution_y, func ) ;
  // matplot::scatter3( solution_x, solution_y, solution_z ) ;
  matplot::show() ;

}

}