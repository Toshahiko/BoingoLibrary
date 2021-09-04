#pragma once
#include "BoingoVisualization.h"

namespace Boingo::Visualization {

class IRangePlot {
public:
  virtual ~IRangePlot() = default ;

  virtual void SetRangeX( const Range& rangeX ) = 0 ;
  virtual void SetRangeY( const Range& rangeY ) = 0 ;
  virtual void SetRangeZ( const Range& rangeZ ) = 0 ;

private:
  virtual bool HasRangeX() const = 0 ;
  virtual bool HasRangeY() const = 0 ;
  virtual bool HasRangeZ() const = 0 ;
  virtual Range RangeX() const = 0 ;
  virtual Range RangeY() const = 0 ;
  virtual Range RangeZ() const = 0 ;
} ;

}