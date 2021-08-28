#pragma once
#include <matplot/matplot.h>

namespace Boingo::Numerical {

using Function2D = std::function<double( double, double )> ;
using Point2D = std::pair<double, double> ;

}