#pragma once
#include <matplot/matplot.h>
#include "Numerical.h"

namespace Boingo {

class Newton2D {
public:
  Newton2D(
      const Function2D& diverge_x,
      const Function2D& diverge_y,
      const Point2D& initial_value
    ) ;

  std::pair<matplot::vector_1d, matplot::vector_1d> Execute() ;

private:
  const Function2D m_diverge_x ;
  const Function2D m_diverge_y ;
  const Point2D m_initial_value ;
} ;

}