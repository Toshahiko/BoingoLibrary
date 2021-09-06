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

void PlotFunc3D() {
  auto r = [](double u, double v) { return 2 + sin(7 * u + 5 * v); };
  auto funx = [r](double u, double v) { return r(u, v) * cos(u) * sin(v); };
  auto funy = [r](double u, double v) { return r(u, v) * sin(u) * sin(v); };
  auto funz = [r](double u, double v) { return r(u, v) * cos(v); };
  Visualization::PlotterFunc3D plotterFunc3D( funx, funy, funz, "mesh" ) ;
  plotterFunc3D.Execute() ;
}

void PlotScatter3D() {
  auto [x, y] = matplot::meshgrid( matplot::linspace( -5.0, 5.0 ), matplot::linspace( -5.0, 5.0 ) ) ;
  auto z = matplot::transform( x, y, func ) ;

  Visualization::Plotter3D plotter3D( std::move( x ), std::move( y ), std::move( z ), "surf" ) ;

  plotter3D.SetRangeX( { 0.0, 1.0 } ) ;
  plotter3D.Execute() ;
}

std::random_device seed ;
std::mt19937_64 engine( seed() ) ;

std::vector<double> NormalDistribution() {
  constexpr double mu = 1.0 ;
  constexpr double sigma = 1.0 ;
  std::normal_distribution<double> dist( 0.0, 1.0 ) ;
  std::vector<double> result ;
  for ( int i = 0 ; i < 1000000 ; ++i ) {
    result.emplace_back( dist( engine ) ) ;
  }

  return result ;
}

void ShowHistogram() {
  std::vector<double> x = NormalDistribution() ;
  auto h = matplot::hist(x);
  std::cout << "Histogram with " << h->num_bins() << " bins" << std::endl;

  matplot::show();
}

}

void StartApi() {
  constexpr int number = 10000 ;
  constexpr double max = 1.0 ;
  constexpr double dt = max/number ;
  std::vector<double> x = matplot::linspace( 0, max, number ) ;

  double W = 0.0 ;
  const auto AnalyticsSolution = [dt, &W] ( double time ) {
    constexpr double mu = 1.0 ;
    constexpr double sigma = 1.0 ;
    std::normal_distribution<double> dist( 0.0, 1.0 ) ;
    W += dist( engine )*std::sqrt( dt ) ;
    return std::exp( mu - std::pow( sigma, 2 )/2.0 + sigma*W ) ;
  } ;

  std::vector<double> y = matplot::transform( x, AnalyticsSolution ) ;

  matplot::plot( x, y, "-o" ) ;
  matplot::show() ; 
}

}