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
constexpr int NUMBER = 10000 ;

std::vector<double> NormalDistribution() {
  std::normal_distribution<double> dist( 0.0, 1.0 ) ;
  std::vector<double> result ;
  for ( int i = 0 ; i < NUMBER ; ++i ) {
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

inline double drift(double x, double t, double mu)
{
    return x*mu;
}

inline double diffusion(double x, double t, double sigma)
{
    return x*sigma;
}

constexpr double mu = 1.0 ;
const double sigma = sqrt( 2.0 ) ;

}

namespace Algorithms {

void InsertionSortAscendent( std::vector<int>& vec ) {
  for ( int j = 1 ; j < vec.size() ; ++j ) {
    int key = vec[j] ;
    int i = j - 1 ;
    while( i >= 0 && vec[i] > key ) {
      vec[i+1] = vec[i] ;
      --i ;
    }
    vec[i+1] = key ;
  }
}

void InsertionSortDescendent( std::vector<int>& vec ) {
  for ( int j = 1 ; j < vec.size() ; ++j ) {
    int key = vec[j] ;
    int i = j - 1 ;
    while( i >= 0 && vec[i] < key ) {
      vec[i+1] = vec[i] ;
      --i ;
    }
    vec[i+1] = key ;
  }
}

}

int CostOneStep( const std::vector<int>& vec, int i ) {
  return abs( vec[i] - vec[i + 1] ) ;
}

int CostTwoStep( const std::vector<int>& vec, int i ) {
  return abs( vec[i] - vec[i + 2] ) ;
}

void DP( const std::vector<int>& vec ) {
  int cost = 0 ;
  for ( size_t i = 0 ; i < vec.size() ; ++i ) {
    cost += CostOneStep( vec, i ) ;
  }

  // 全てのパターンを攻略する
  // ステップの合計がサイズ分である必要がある。
  // 方法1:1,2を使って1ステップ2ステップを決めるvectorを作成する。
  // 方法2:bitを使ってどこで二段飛ばしにするかを表現する。
  int newcost = 0 ;
  newcost = cost - CostOneStep( vec, vec.size() - 1 ) - CostOneStep( vec, vec.size() - 2 ) ;

  newcost += CostTwoStep( vec, vec.size() - 2 ) ;

}

std::vector<int> GenerateNext( const std::vector<int>& vec ) {
  // 2を探して、その前の二つの1を削除する。
  std::vector<int> nextVec{ vec.cbegin(), vec.cend() } ;
  const auto pos2 = std::find( nextVec.cbegin(), nextVec.cend(), 2 ) ;
  if ( std::distance( nextVec.cbegin(), pos2 ) <= 1 ) return std::vector<int>() ;

  nextVec.erase( pos2 - 2, pos2 ) ;
  // 2をpush_backする。
  nextVec.push_back( 2 ) ;

  return nextVec ;
}

std::vector<std::vector<int>> GenerateOriginalSteps( const size_t step_size ) {
  std::vector<int> vec( step_size, 1 ) ;
  std::vector<std::vector<int>> results{ vec } ;
  while ( true ) {
    vec = GenerateNext( vec );
    if ( vec.empty() ) break ;
    results.push_back( vec ) ;
  }

  return results ;
}

std::vector<std::vector<int>> GenerateSteps( const size_t step_size ) {
  auto steps = GenerateOriginalSteps( step_size ) ;
  std::vector<std::vector<int>> results ;
  for ( auto& step : steps ) {
    do {
      results.push_back( step ) ;
    } while ( std::next_permutation( step.begin(), step.end() ) );
  }
  return results ;
}

std::vector<int> CalculateScores(
  const std::vector<std::vector<int>>& steps,
  const std::vector<int>&              costs
  ) {
  std::vector<int> scores ;
  scores.reserve( steps.size() ) ;
  for ( const auto& path : steps ) {
    int cost = 0 ;
    int length = 0 ;
    for ( int i = 0 ; i < path.size() - 1 ; ++i ) {
      if ( path[i] == 1 ) {
        cost += CostOneStep( costs, length );
      } else if ( path[i] == 2 ) {
        cost += CostTwoStep( costs, length );
      }
      length += path[i] ;
    }
    scores.push_back( cost ) ;
  }
  return scores ;
}

void ShowSteps( const std::vector<std::vector<int>>& steps ) {
  for ( const auto& step : steps ) {
    std::for_each( step.cbegin(), step.cend(),
      []( const int value ) { std::cout << value ; } ) ;

    std::cout << std::endl ;
  }
}

void StartApi() {
  std::vector<int> costs{ 2, 3, 6, 3, 7, 7, 8 } ;
  const auto results = GenerateSteps( costs.size() ) ;
  const auto scores = CalculateScores( results, costs ) ;

  for ( const auto score : scores ) {
    std::cout << "score: " << score << std::endl ;
  }

}

}