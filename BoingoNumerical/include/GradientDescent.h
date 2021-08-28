#pragma once
#include <matplot/matplot.h>
#include "Numerical.h"

namespace Boingo::Numerical {

class GradientDescent {
public:
  GradientDescent(
    const Function2D& func,
    const Function2D& diverge_x,
    const Function2D& diverge_y,
    const Point2D& initial_value,
    const double step_width
  ) ;

  std::pair<matplot::vector_1d, matplot::vector_1d> Execute() ;

private:
  double StepWidth(
    const double x,
    const double y,
    const double d_x,
    const double d_y
  ) ;

private:
  const Function2D m_func ;
  const Function2D m_diverge_x ;
  const Function2D m_diverge_y ;
  const Point2D    m_initial_value ;
        double     m_step_width ;
} ;

} // namespace Boingo